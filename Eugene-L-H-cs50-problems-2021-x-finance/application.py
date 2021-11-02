import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, strong_password

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Count number of bought and sold shares for each company
    rows = db.execute("SELECT * FROM purchases WHERE uid = :uid", uid = session["user_id"])
    global company_shares
    company_shares = {}

    for row in rows:
        if row["symbol"] not in company_shares:
            company_shares[row["symbol"]] = row["amount"]
        else:
            if row["type"] == 'bought':
                company_shares[row["symbol"]] = company_shares[row["symbol"]] + row["amount"]
            elif row["type"] == 'sold':
                company_shares[row["symbol"]] = company_shares[row["symbol"]] - row["amount"]

    # Count user balance (total stocks + cash)
    row = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])
    total = row[0]["cash"]
    for symbol, amount in company_shares.items():
        if amount > 0:
            stock = lookup(symbol)
            total += stock["price"] * amount


    return render_template("index.html",
                            shares = company_shares,
                            lookup = lookup,
                            usd = usd,
                            cash = row[0]["cash"],
                            balance = total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # Check that the symbol is valid and that there are shares
    if request.method == 'POST':
        symbol = request.form.get("symbol")

        if lookup(symbol) == None:
            return apology("Not a valid symbol")

        try:
            if int(request.form.get("shares")) < 1:
                return apology("Not enough shares", 400)
        except ValueError:
            return apology("Please enter a number of shares.", 400)

        stock_price = lookup(symbol)["price"]
        company = lookup(symbol)["name"]

        row = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
        user_cash = row[0]["cash"]

        # Can user affortd purchase?
        purchase_price = stock_price * float(request.form.get("shares"))
        if purchase_price > user_cash:
            return apology("Isufficient funds")

        # Log purchase into database
        db.execute("INSERT INTO purchases (uid, company, symbol, amount, price, type) VALUES (:uid,:company,:symbol,:amount,:price,'bought')",
                    uid = session["user_id"],
                    company = company,
                    symbol = lookup(symbol)["symbol"],
                    amount = float(request.form.get("shares")),
                    price = stock_price)

        # Update user cash balance
        balance = user_cash - purchase_price
        db.execute("UPDATE users SET cash = :cash WHERE id = :id",
                    cash = balance,
                    id = session["user_id"])

        flash("Purchased")

        return redirect("/")

    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    rows = db.execute("SELECT * FROM purchases WHERE uid = :uid", uid = session["user_id"])
    return render_template("history.html", history = rows, usd = usd)

    #return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        symbol = request.form.get("symbol")
        stock = lookup(symbol)

        if stock == None:
            return apology("Symbol not valid")

        return render_template("quoted.html",
                                company = stock["name"],
                                symbol = stock["symbol"],
                                share_price = usd(stock["price"]))

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        # Get username
        if not request.form.get("username"):
            return apology("Must enter Username", 400)

        rows = db.execute("SELECT * FROM users WHERE username=:username", username = request.form.get("username"))
        if len(rows) > 0: # Meaning that there is user with that name already.
            return apology("Username already taken", 400)

        # Confirm password submitted
        if not request.form.get("password"):
            return apology("Please enter a password.", 400)


        # Be sure that new user's password contains special characters, numbers, uppercase
        password = request.form.get("password")

        if strong_password(password):
            pass
        else:
            return apology("Please enter a password that contains at least 1 uppercase char, 1 number and one special char.", 400)

        # Password match
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords do not match.", 400)

        # Create new user in database
        user = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                        username = request.form.get("username"),
                        hash = generate_password_hash(request.form.get("password")))

        # Remember user
        session["user"] = user

        # Back to homepage
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == 'POST':
        # Ensure a symbol is selected
        if request.form.get("symbol") == None:
            return apology("Please enter a valid symbol.")

        # Ensure number of shares is a positive integer
        if int(request.form.get("shares")) < 1:
            return apology("Please input 1 or more shares.")

        # Ensure a valid number of shares is sold
        if int(request.form.get("shares")) > company_shares[request.form.get("symbol")]:
            return apology("too many shares")

        # Update database
        stock = lookup(request.form.get("symbol"))
        rows = db.execute("SELECT * FROM users WHERE id = :id", id = session["user_id"])
        new_cash = rows[0]["cash"] + (stock["price"] * int(request.form.get("shares")))

        db.execute("UPDATE users SET cash = :cash WHERE id = :id",
                    cash = new_cash,
                    id = session["user_id"])
        db.execute("INSERT INTO purchases (uid, company, symbol, price, amount, type) VALUES (:uid,:company,:symbol,:price,:amount,'sold')",
                    uid = session["user_id"],
                    company = stock["name"],
                    symbol = stock["symbol"],
                    price = stock["price"],
                    amount = int(request.form.get("shares")))

        if int(request.form.get("shares")) == 1:
            flash("Stock sold.")
        else:
            flash("Stocks sold")

        return redirect("/")

    else:
        return render_template("sell.html", symbols = company_shares)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
