SET STATISTICS TIME ON

SELECT TOP 5 maker, model
--		, [speed score], [ram score], [hd score], [screen score], performance, price, [performance-price ratio]
FROM (SELECT maker, model,
--		[speed score], [ram score], [hd score], [screen score], performance, price,
		[performance-price ratio] = performance / price
	FROM (SELECT maker, model, price,
--			[speed score], [ram score], [hd score], [screen score],
			performance = [speed score] + [ram score] + [hd score] + [screen score]
		FROM (SELECT Product.maker, Laptop.model, price,
				[speed score] = speed * 2000.0,
				[ram score] = ram * 1.0,
				[hd score] = hd * 4.0,
				[screen score] = screen * 50.0
			FROM dbo.Laptop, dbo.Product
			WHERE Laptop.model = Product.model) weig) perf) ratio
ORDER BY [performance-price ratio] DESC

SET STATISTICS TIME OFF