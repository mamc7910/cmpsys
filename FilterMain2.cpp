double
applyFilter(struct Filter *filter, cs1300bmp *input, cs1300bmp *output)
{

  long long cycStart, cycStop;

  cycStart = rdtscll();
  output -> width = input -> width;
  output -> height = input -> height;
  int filterSize = filter->getSize();
  int inputWidth = input->width - 1;
  int inputHeight = input->height - 1;
  for(int col = 1; col < inputWidth; col = col + 1) {
    for(int row = 1; row < inputHeight; row = row + 1) { //remove for loop for planes
	int green = 0;
    int red = 0;
    int blue = 0;
    int j;
	for (j = 0; j < filterSize; j++) {
      int i;
	  for (i = 0; i < filterSize; i++) {	
         red += input->color[COLOR_RED][row + i - 1][col + j - 1] * filter->get(i, j);
	     green += input->color[COLOR_GREEN][row + i - 1][col + j - 1] * filter->get(i, j);
         blue += input->color[COLOR_BLUE][row + i - 1][col + j - 1] * filter->get(i, j);
	  }
	}
	
	red /= filter->getDivisor();
    green /= filter->getDivisor();
    blue /= filter->getDivisor();

	if (red < 0){
    red = 0;
    }
    if (red > 255){
    red = 255;
    }
    if (green < 0){
    green = 0;
    }
    if (green > 255){green = 255;}
    if (blue < 0){blue = 0;}
    if (blue > 255){blue = 255;}
    output->color[COLOR_RED][row][col] = red;
    output->color[COLOR_GREEN][row][col] = green;
    output->color[COLOR_BLUE][row][col] = blue;
    }
  }

  cycStop = rdtscll();
  double diff = cycStop - cycStart;
  double diffPerPixel = diff / (output -> width * output -> height);
  fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
	  diff, diff / (output -> width * output -> height));
  return diffPerPixel;
}
