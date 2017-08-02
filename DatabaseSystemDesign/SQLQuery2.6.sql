SET STATISTICS TIME ON

SELECT DISTINCT t1.maker
FROM (SELECT pd.maker, pd.model
	FROM dbo.Product pd INNER JOIN (SELECT model
		FROM dbo.PC
		WHERE speed >= 3.0
		UNION
		SELECT model
		FROM dbo.Laptop
		WHERE speed >= 3.0
		) md ON pd.model = md.model
	) t1 INNER JOIN (SELECT pd.maker, pd.model
	FROM dbo.Product pd INNER JOIN (SELECT model
		FROM dbo.PC
		WHERE speed >= 3.0
		UNION
		SELECT model
		FROM dbo.Laptop
		WHERE speed >= 3.0
		) md ON pd.model = md.model
	) t2 ON t1.maker = t2.maker
AND t1.model != t2.model

SET STATISTICS TIME OFF