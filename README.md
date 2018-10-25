# ZestyVesty

Here are some basic things about the light matrix.

1. As of now, when running programs to display on the light matrix, put this command line after the call to the file to run. 
--led-slowdown-gpio=2 --led-rows=32 --led-cols=64

2. We want to turn down the brightness of the matrix so that it will consume less power. Do this by putting this command after call to file to run. (default is 100)
--led-brightness=<50>

3. A cool and easy function we could print on the matrix is a clock. Do this by running sudo ./clock -f ../fonts/7x13.bdf --led-chain=2 -d "%H:%M:%S"

4. We initially wanted to vertically orient our matrix. I'm a little unsure if this would mess up all the code from the github I downloaded, but we can rotate the canvas by calling   options.pixel_mapper_config = "Rotate:90";


