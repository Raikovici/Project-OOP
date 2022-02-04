SELECT * FROM Products
WHERE ProductName like '_a%'

SELECT *   
FROM Orders
WHERE DATEPART(Q, OrderDate) = 2 AND DATEPART(YEAR, OrderDate) = 1997 

--inreg din Orders ziua din col shipdate > 10
--freight < 50, customerID contine G, ord desc dupa orderdate

SELECT *
FROM Orders
WHERE DATEPART(DAY, ShippedDate) > 10 AND Freight < 50 AND CustomerID like '%G%'
ORDER BY OrderDate DESC

--deviatia std a unitprice tuturor produselor
SELECT STDEV(UnitPrice) AS 'DEVIATIE STANDARD'
FROM Products

SELECT UnitPrice AS Pret
FROM Products