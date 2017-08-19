SET STATISTICS TIME ON

SELECT maker
FROM dbo.Product
WHERE type = 'laptop'
EXCEPT
SELECT maker
FROM dbo.Product
WHERE type = 'pc'

SET STATISTICS TIME OFF