This repo include two basic color interpolation algorithm
1.Bilinear interpolation
2.Nearest Neighbor interpolation

Also there is a function called "Color2Bayer". This function is for someone who doesnt have bayer image. \
You can use this function to turn the RGB image into bayer image(GRBG, GBRG, RGGB, BGGR)

In bayer image, we only have single color value in one pixel, which means there is only one channel in pixel that has value.
It is because that in morden days, most of the CMOS sensor cameras only have one sensor in one pixel to save space and cost.
So there is bayer patten(Color filter) place above the CMOS sensr to get the R or G ot B color information in incident light for every single pixel.
In order to get the real color image, we interpolate the patterned R,G and B color information for this purpose.

Nearest Neighbor color interpolation is taking color information from its neighbor. For example:
We had GRBG 4 pixels in bayer image whose index are [0,0], [0,1], [1,0], [1,1].
We get the R and B color information of [0,0] from [0,1] and [1,0].
And we get the G color infromation of [0,1] from [1,0].
... and so on


Bilinear interpolation is similar to the Nearest Neighbor interpolation, but it took more color infromation from neighbor pixels.
And it average the color information from its neighbor pixels.


Here is the original image(took by my iphone6)

![alt text](https://raw.githubusercontent.com/Gambler1993/Basic_Color_Interpolation/master/imgs/original_img.bmp)

This is the bayer image by import the original image into Color2Bayer function

![alt text](https://raw.githubusercontent.com/Gambler1993/Basic_Color_Interpolation/master/imgs/bayer_pattern_img.bmp)

This is the result of Nearest Neighbor color interpolation

![alt text](https://raw.githubusercontent.com/Gambler1993/Basic_Color_Interpolation/master/imgs/NearestNeighbor_dst.bmp)

This is the result of Bilinear color interpolation

![alt text](https://raw.githubusercontent.com/Gambler1993/Basic_Color_Interpolation/master/imgs/Bilnear_dst.bmp)