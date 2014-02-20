/* 
 * File:   main.c
 * Author: Terence-Lee "Zinglish" Davis
 * Site:   https://github.com/Zinglish
 * Source: https://github.com/Zinglish/cod4-patch-customconsole
 * 
 * Created on 19 February 2014, 15:53
 */

#include <stdio.h>

void print_banner();

/* Inclusive patch start and end with data before and after */
unsigned int patch_points[4][2] =
{ 
	{ 0x00124DDF, 0x00124DE2 },
	{ 0x00124DE9, 0x00124DEC },
	{ 0x00125407, 0x0012540A },
	{ 0x00125411, 0x00125414 }
};
unsigned char patch_data[4][2][4] = 
{
	{ 
		{ 0x63, 0x6F, 0x6E, 0x73 },
		{ 0x5E, 0x37, 0x5E, 0x37 }
	},
	{
		{ 0x6F, 0x6C, 0x65, 0x3A },
		{ 0x5E, 0x37, 0x5E, 0x37 }
	},
	{ 
		{ 0x63, 0x6F, 0x6E, 0x73 },
		{ 0x5E, 0x37, 0x5E, 0x37 }
	},
	{
		{ 0x6F, 0x6C, 0x65, 0x3A },
		{ 0x5E, 0x37, 0x5E, 0x37 }
	},
};

int main(int argc, char** argv)
{
	print_banner();
	
	/* Ensure we have the filename as the argument */
	if(argc != 2)
	{
		printf("Usage: %s [filename]\n", argv[0]);
		printf("Where [filename] is the CoD4 server ELF\n");
	}
	/* Open the ELF for reading and buffering to patch the short byte */
	else
	{
		FILE* file = fopen(argv[1], "rb+");
		
		if(file == 0)
			printf("Could not open %s for reading/writing\n", argv[1]);
		else
		{
			char byte_check_buf[1];
			unsigned int s_patch_points = sizeof(patch_points) / sizeof(patch_points[0]);
			
			/* Loop through each patch point and patch and make sure the 
			   byte that needs to be patched is there, then attempt a patch */
			for(unsigned int patch_no=0;patch_no<s_patch_points;patch_no++)
			{
				printf("Checking conditions for subpatch %i\n", patch_no + 1);
				
				fseek(file, patch_points[patch_no][0] - 1, SEEK_SET);
				for(unsigned int i=0;i<sizeof(patch_data[patch_no][0]);i++)
				{
					fread(&byte_check_buf, 1, 1, file);
					if(byte_check_buf[0] != patch_data[patch_no][0][i])
					{
						printf("Check failed, wrong ELF or patch already done\n");
						return(0);
					}
				}
			}
			
			printf("Check successful, correct ELF, now patching\n");
			
			/* Now we write the patch */
			for(unsigned int patch_no=0;patch_no<s_patch_points;patch_no++)
			{
				printf("Writing subpatch %i\n", patch_no + 1);
				
				fseek(file, patch_points[patch_no][0] - 1, SEEK_SET);
				for(unsigned int i=0;i<sizeof(patch_data[patch_no][0]);i++)
				{
					fwrite(&patch_data[patch_no][1][i], 1, 1, file);
				}
			}
			
			/* Now we check if the subpatch was successful */
			for(unsigned int patch_no=0;patch_no<s_patch_points;patch_no++)
			{
				fseek(file, patch_points[patch_no][0] - 1, SEEK_SET);
				for(unsigned int i=0;i<sizeof(patch_data[patch_no][0]);i++)
				{
					fread(&byte_check_buf, 1, 1, file);
					if(byte_check_buf[0] != patch_data[patch_no][1][i])
					{
						printf("Patch has failed\n");
						return(0);
					}
				}
			}
			
			printf("Patch was a great success, enjoy your freedom\n");
		}
	}
	
	return(1);
}

void print_banner()
{
	printf("# ==================================================================== #\n"
			"#                                                                      #\n"
			"#    ________                       ___                 __             #\n"
			"#   /\\_____  \\  __    Zinglish     /\\_ \\    __         /\\ \\            #\n"
			"#   \\/____//'/'/\\_\\    ___      __ \\//\\ \\  /\\_\\    ____\\ \\ \\___        #\n"
			"#        //'/' \\/\\ \\ /' _ `\\  /'_ `\\ \\ \\ \\ \\/\\ \\  /',__\\\\ \\  _ `\\      #\n"
			"#       //'/'___\\ \\ \\/\\ \\/\\ \\/\\ \\_\\ \\ \\_\\ \\_\\ \\ \\/\\__, `\\\\ \\ \\ \\ \\     #\n"
			"#       /\\_______\\ \\_\\ \\_\\ \\_\\ \\____ \\/\\____\\\\ \\_\\/\\____/ \\ \\_\\ \\_\\    #\n"
			"#       \\/_______/\\/_/\\/_/\\/_/\\/___/\\ \\/____/ \\/_/\\/___/   \\/_/\\/_/    #\n"
			"#                               /\\____/                                #\n"
			"#                               \\/___/   - Custom Console Patcher      #\n"
			"#                                                                      #\n"
			"#                                                                      #\n"
			"#                   .- https://github.com/Zinglish -.                  #\n"
			"#                                                                      #\n"
			"# ==================================================================== #\n\n");
}