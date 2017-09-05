网格标准：谷歌经纬度网格（GoogleCRS84Quad）    注：详细标准可从geoserver的gridsets查看。

Coordinate Reference System:EPSG:4326

Gridset bounds:(-180,-90,180,90)

Tile (width,height) in pixels *  :(256,256)



瓦片分割程序：

1.线程数默认为：100 （可选择输入）

2.目前只能分割.tif格式图片，只支持生成.png文件

3.瓦片保存路径：不支持同名文件替换，因此路径下不能存在与即将生成的瓦片同名的文件存在。

4.瓦片级别支持（6-24）


瓦片目录结构：

存储路径下:

EPSG_4326_level     (6<=level<=24)  level占两位，如：EPSG_4326_06  ，EPSG_4326_11


瓦片级别下子文件夹及瓦片命名:


level：6-11

每个子文件夹放 num = 2^(floor(level/2)+1)个瓦片。

子文件夹名称：设列号为i，行号为j。   则该瓦片存于子文件夹：（i/num取整)_（j/num取整）。


关于如何决定i，j，（i/num取整)，j/num取整）的位数，即在数字前加0补位(设：目录位数为x，瓦片名字中数字位数为y，y=2x)：

例如：子文件夹：06_02  则x=2; 瓦片名：0105_0046.png   则y=4。

当level（6-11） x=2,y=4
当level (12-17）x=3,y=6
当level (18-24) x=4,y=8 