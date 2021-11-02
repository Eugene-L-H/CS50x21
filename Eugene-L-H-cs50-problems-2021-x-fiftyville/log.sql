-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT description -- That's the column we're interested in.
FROM crime_scene_reports -- That's the table we're querieing from.
WHERE month = 7 AND day = 28
AND street = "Chamberlin Street";
--
SELECT transcript
FROM interviews
WHERE day = 28
AND month = 7
AND YEAR = 2020
AND transcript like "%courthouse%";

-- Search licence plate from car mentioned in transcript
SELECT name
FROM courthouse_security_logs
SELECT
WHERE day = 28
AND month = 7
AND hour = 10
AND (minute >= 15 AND minute < 25)
AND activity = "exit"

SELECT amount
FROM atm_transactions
WHERE day = 28
AND month = 7
AND YEAR = 2020
AND atm_location = "Fifer Street"
AND transaction_type LIKE "Withdraw";
-- Search phone records for phone call less than 1min 1015-1025
SELECT caller
FROM phone_calls
WHERE year = 2020
AND month = 7
AND day = 28
AND duration < 1;
