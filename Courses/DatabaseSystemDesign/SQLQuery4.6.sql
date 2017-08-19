SET STATISTICS TIME ON

SELECT maker, AVG(screen) AS 'avg screen'
FROM dbo.Laptop, dbo.Product
WHERE Laptop.model = Product.model
GROUP BY maker

SET STATISTICS TIME OFF