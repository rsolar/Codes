SET STATISTICS TIME ON

SELECT maker,
	point = SUM([rank])
FROM (SELECT maker,
--		model, [speed score], [ram score], [hd score], price, performance, [performance-price ratio],
		[rank] = RANK() OVER (ORDER BY [performance-price ratio] ASC)
	FROM (SELECT maker,
--			model, [speed score], [ram score], [hd score], price, performance,
			[performance-price ratio] = performance / price
		FROM (SELECT maker, price,
--				model, [speed score], [ram score], [hd score],
				performance = [speed score] + [ram score] + [hd score]
			FROM (SELECT Product.maker, price,
--					PC.model,
					[speed score] = speed * 2000.0,
					[ram score] = ram * 1.0,
					[hd score] = hd * 4.0
				FROM dbo.PC, dbo.Product
				WHERE PC.model = Product.model) weig) perf) ratio) rnk
GROUP BY maker
ORDER BY point DESC

SET STATISTICS TIME OFF