SET STATISTICS TIME ON

SELECT AVG(price) AS 'avg price'
FROM dbo.PC
WHERE speed > 2.0

SET STATISTICS TIME OFF