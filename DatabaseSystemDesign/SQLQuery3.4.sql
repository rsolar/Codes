SET STATISTICS TIME ON

SELECT tmp.model
FROM (SELECT model, price
	FROM dbo.PC
	UNION
	SELECT model, price
	FROM dbo.Laptop
	UNION
	SELECT model, price
	FROM dbo.Printer
	) tmp
WHERE tmp.price >= ALL (SELECT price
	FROM dbo.PC
	UNION
	SELECT price
	FROM dbo.Laptop
	UNION
	SELECT price
	FROM dbo.Printer)

SET STATISTICS TIME OFF