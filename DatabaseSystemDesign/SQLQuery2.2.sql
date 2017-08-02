SET STATISTICS TIME ON

SELECT PC.model, PC.price
FROM dbo.Product, dbo.PC
WHERE Product.model = PC.model
	AND Product.maker = 'B'
UNION
SELECT Laptop.model, Laptop.price
FROM dbo.Product, dbo.Laptop
WHERE Product.model = Laptop.model
	AND Product.maker = 'B'
UNION
SELECT Printer.model, Printer.price
FROM dbo.Product, dbo.Printer
WHERE Product.model = Printer.model
	AND Product.maker = 'B'

SET STATISTICS TIME OFF