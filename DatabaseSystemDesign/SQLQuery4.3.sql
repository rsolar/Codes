SET STATISTICS TIME ON

SELECT AVG(price)
FROM dbo.PC, dbo.Product
WHERE Product.model = PC.model
	AND maker = 'A'

SET STATISTICS TIME OFF