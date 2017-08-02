SET STATISTICS TIME ON

SELECT maker, MAX(price) AS 'max price'
FROM dbo.Product, dbo.PC
WHERE product.model = PC.model
	AND type = 'pc'
GROUP BY maker

SET STATISTICS TIME OFF