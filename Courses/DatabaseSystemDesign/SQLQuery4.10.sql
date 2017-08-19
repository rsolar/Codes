SET STATISTICS TIME ON

SELECT Product.maker, AVG(hd) AS 'avg hd'
FROM dbo.PC, dbo.Product, (SELECT maker
	FROM product
	WHERE type = 'printer'
	) pmaker
WHERE Product.maker = pmaker.maker
	AND Product.model = PC.model
GROUP BY Product.maker

SET STATISTICS TIME OFF