SET STATISTICS TIME ON

SELECT AVG(price) AS 'avg price'
FROM (SELECT model, price
	FROM dbo.PC
	UNION
	SELECT model, price
	FROM dbo.Laptop) tmp, dbo.Product
WHERE tmp.model = Product.model
	AND Product.maker = 'D'

SET STATISTICS TIME OFF