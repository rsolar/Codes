SET STATISTICS TIME ON

SELECT DISTINCT maker
FROM dbo.Product
WHERE model IN (SELECT model
	FROM dbo.Printer
	WHERE price <= ALL (SELECT price
			FROM dbo.Printer)
		AND color = 'true')

SET STATISTICS TIME OFF