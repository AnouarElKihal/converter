#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

// from DECIMAL to BINARY
int dtob(int num) {
  int rem = 0, bin = 0, place = 1;
  while (num) {
    rem = num % 2;
    num /= 2;
    bin += rem * place;
    place *= 10;
  }
  return bin;
}

// from BINARY to DECIMAL
int btod(int bin) {
  char stringNumber[10];
  sprintf(stringNumber, "%d", bin);
  int result = 0, len = strlen(stringNumber);

  for (int i = 0; i < len; i++) {
    if (stringNumber[i] == '1') {
      result = result + (1 * pow(2, len - i - 1));
    } else if (stringNumber[i] == '0') {
      result = result + (0 * pow(2, len - i - 1));
    } else {
      printf("ERROR\n");
      exit(0);
    }
  }

  return result;
}

// from STRING to BINARY
char *stob(char *s) {
  if (s == NULL)
    return 0;
  int len = strlen(s);
  char *binary = malloc(len * 8 + 1);
  for (int i = 0; i < len; i++) {
    char ch = s[i];
    for (int j = 7; j >= 0; j--) {
      if (ch & (1 << j)) {
        strcat(binary, "1");
      } else {
        strcat(binary, "0");
      }
    }
  }
  return binary;
}

// from BINARY to ASCII
char btoa(char *bin) {
  int len = strlen(bin);
  int result = 0;
  char newArray[len];
  char finalResult;

  int x = len - 1;
  for (int j = 0; j < len; j++) {
    newArray[j] = bin[x];
    x--;
    if (newArray[j] == '1') {
      result += pow(2, j);
    }
  }

  return result;
}

// from COLORED IMAGE to GRAY one
int ctog(int choice) {
  int width, height, channels;

  if (choice == 1) {
    printf("YOU CHOSE 'JPG'...\n");
    // change 'image.jpg' with your image name
    unsigned char *img = stbi_load("image.jpg", &width, &height, &channels, 0);
    if (img == NULL) {
      printf("Error in loading the image\n");
      exit(1);
    }
    printf(
        "Loaded image with a width of %dpx, a height of %dpx and %d channels\n",
        width, height, channels);

    size_t img_size = width * height * channels;
    int gray_channels = channels == 4 ? 2 : 1;
    size_t gray_img_size = width * height * gray_channels;

    unsigned char *gray_img = malloc(gray_img_size);
    if (gray_img == NULL) {
      printf("Unable to allocate memory for the gray image\n");
      exit(1);
    }

    for (unsigned char *p = img, *pg = gray_img; p != img + img_size;
         p += channels, pg += gray_channels) {
      *pg = (uint8_t)((*p + *(p + 1) + *(p + 2)) / 3.0);
      if (channels == 4) {
        *(pg + 1) = *(p + 3);
      }
    }

    stbi_write_jpg("grayImage.jpg", width, height, gray_channels, gray_img,
                   100);

    stbi_image_free(img);
    free(gray_img);

  } else if (choice == 2) {
    printf("YOU CHOSE 'PNG'...\n");
    // change 'image.png' with your image name
    unsigned char *img = stbi_load("image.png", &width, &height, &channels, 0);
    if (img == NULL) {
      printf("Error in loading the image\n");
      exit(1);
    }
    printf(
        "Loaded image with a width of %dpx, a height of %dpx and %d channels\n",
        width, height, channels);

    size_t img_size = width * height * channels;
    int gray_channels = channels == 4 ? 2 : 1;
    size_t gray_img_size = width * height * gray_channels;

    unsigned char *gray_img = malloc(gray_img_size);
    if (gray_img == NULL) {
      printf("Unable to allocate memory for the gray image\n");
      exit(1);
    }

    for (unsigned char *p = img, *pg = gray_img; p != img + img_size;
         p += channels, pg += gray_channels) {
      *pg = (uint8_t)((*p + *(p + 1) + *(p + 2)) / 3.0);
      if (channels == 4) {
        *(pg + 1) = *(p + 3);
      }
    }

    stbi_write_png("grayImage.png", width, height, gray_channels, gray_img,
                   width * gray_channels);

    stbi_image_free(img);
    free(gray_img);

  } else {
    printf("The image must be JPG or PNG\n");
    exit(1);
  }

  return 0;
}

// from COLORED IMAGE to SEPIA one
int ctos(int choice) {
  int width, height, channels;
  if (choice == 1) {
    printf("YOU CHOSE 'JPG'...\n");
    // change 'image.jpg' with your image name
    unsigned char *img = stbi_load("image.jpg", &width, &height, &channels, 0);
    if (img == NULL) {
      printf("Error in loading the image\n");
      exit(1);
    }
    printf(
        "Loaded image with a width of %dpx, a height of %dpx and %d channels\n",
        width, height, channels);

    size_t img_size = width * height * channels;

    unsigned char *sepia_img = malloc(img_size);
    if (sepia_img == NULL) {
      printf("Unable to allocate memory for the sepia image.\n");
      exit(1);
    }

    for (unsigned char *p = img, *pg = sepia_img; p != img + img_size;
         p += channels, pg += channels) {
      *pg = (uint8_t)fmin(0.393 * *p + 0.769 * *(p + 1) + 0.189 * *(p + 2),
                          255.0); // red
      *(pg + 1) =
          (uint8_t)fmin(0.349 * *p + 0.686 * *(p + 1) + 0.168 * *(p + 2),
                        255.0); // green
      *(pg + 2) =
          (uint8_t)fmin(0.272 * *p + 0.534 * *(p + 1) + 0.131 * *(p + 2),
                        255.0); // blue
      if (channels == 4) {
        *(pg + 3) = *(p + 3);
      }
    }
    stbi_write_jpg("sepiaImage.jpg", width, height, channels, sepia_img, 100);

    stbi_image_free(img);
    free(sepia_img);

  } else if (choice == 2) {
    printf("YOU CHOSE 'PNG'...\n");
    // change 'image.png' with your image name
    unsigned char *img = stbi_load("image.png", &width, &height, &channels, 0);
    if (img == NULL) {
      printf("Error in loading the image\n");
      exit(1);
    }
    printf(
        "Loaded image with a width of %dpx, a height of %dpx and %d channels\n",
        width, height, channels);

    size_t img_size = width * height * channels;

    unsigned char *sepia_img = malloc(img_size);
    if (sepia_img == NULL) {
      printf("Unable to allocate memory for the sepia image.\n");
      exit(1);
    }

    for (unsigned char *p = img, *pg = sepia_img; p != img + img_size;
         p += channels, pg += channels) {
      *pg = (uint8_t)fmin(0.393 * *p + 0.769 * *(p + 1) + 0.189 * *(p + 2),
                          255.0); // red
      *(pg + 1) =
          (uint8_t)fmin(0.349 * *p + 0.686 * *(p + 1) + 0.168 * *(p + 2),
                        255.0); // green
      *(pg + 2) =
          (uint8_t)fmin(0.272 * *p + 0.534 * *(p + 1) + 0.131 * *(p + 2),
                        255.0); // blue
      if (channels == 4) {
        *(pg + 3) = *(p + 3);
      }
    }
    stbi_write_png("sepiaImage.png", width, height, channels, sepia_img, width * channels);

    stbi_image_free(img);
    free(sepia_img);

  } else {
    printf("The image must be JPG or PNG\n");
    exit(1);
  }

  return 0;
}

int main() {
  while(1){
    int selection;
    printf("1) Convert a Decimal number to Binary code\n2) Convert a Binary code to Decimal number\n3) Convert a String to Binary code\n4) Convert a Binary code to ASCII\n5) Convert a Colored Image to a Gray one\n6) Convert a Colored Image to a Sepia one\n7) Quit\n");
    printf("> ");
    scanf("%d", &selection);
    switch (selection) {
      case 1:
        printf("DECIMAL NUMBER -> BINARY CODE\n");
        int dn;
        printf("Enter the decimal number: ");
        scanf("%d", &dn);
        printf("Result: %d\n", dtob(dn));
        break;
      case 2:
        printf("BINARY CODE -> DECIMAL NUMBER\n");
        int bc;
        printf("Enter the binary code: ");
        scanf("%d", &bc);
        printf("Result: %d\n", btod(bc));
        break;
      case 3:
        printf("STRING -> BINARY CODE\n");
        char *output = malloc(sizeof(char) * 8);
        printf("Enter the string: ");
        scanf("%s", output);
        printf("Result: %s\n", stob(output));
        break;
      case 4:
        printf("BINARY CODE -> ASCII\n");
        char *bin = malloc(sizeof(char) * 8);
        printf("Enter the binary code: ");
        scanf("%s", bin);
        printf("Result: %c\n", btoa(bin));
        return 0;
        break;
      case 5:
        printf("COLORED IMAGE -> GRAY IMAGE\n");
        int choice1;
        printf("Inserisci il tipo di file inizile(Jpg=1;Png=2): ");
        scanf("%d", &choice1);
        ctog(choice1);
        break;
      case 6:
        printf("COLORED IMAGE -> SEPIA IMAGE\n");
        int choice2;
        printf("Inserisci il tipo di file inizile(Jpg=1;Png=2): ");
        scanf("%d", &choice2);
        ctos(choice2);
        break;
      case 7:
        exit(1);
        break;
      default:
        printf("Something went wrong... Select a number in the list!\n");
        break;
    }
  }

}
