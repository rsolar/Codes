SET STATISTICS TIME ON

SELECT Product.maker, PC.model
FROM dbo.Product, dbo.PC
WHERE Product.model = PC.model
	AND PC.speed = (
		SELECT speed
		FROM dbo.PC GROUP BY speed
		HAVING COUNT(*) >= ALL (SELECT COUNT(*)
			FROM dbo.PC GROUP BY speed)
		)
	AND PC.ram = (
		SELECT ram
		FROM dbo.PC GROUP BY ram
		HAVING COUNT(*) >= ALL (SELECT COUNT(*)
			FROM dbo.PC GROUP BY ram)
		)
	AND PC.hd = (
		SELECT hd
		FROM dbo.PC GROUP BY hd
		HAVING COUNT(*) >= ALL (SELECT COUNT(*)
			FROM dbo.PC GROUP BY hd)
		)

SET STATISTICS TIME OFF