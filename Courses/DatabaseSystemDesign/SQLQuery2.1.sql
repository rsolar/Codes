SET STATISTICS TIME ON

SELECT maker, speed
FROM dbo.Product, dbo.PC
WHERE Product.model = PC.model
	AND hd >= 30

SET STATISTICS TIME OFF