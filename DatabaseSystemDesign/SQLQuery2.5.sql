SET STATISTICS TIME ON

SELECT pc1.model AS 'model1', pc2.model AS 'model2'
FROM dbo.PC pc1, dbo.PC pc2
WHERE pc1.speed = pc2.speed
	AND pc1.ram = pc2.ram
	AND pc1.model < pc2.model

SET STATISTICS TIME OFF