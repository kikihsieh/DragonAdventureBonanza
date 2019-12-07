import os
import re
import sys
from PIL import Image, ImageDraw

def main():
	map_selection = input("Please select a map:\n\t[1] Forest\n\t[2] Cave\n\t[3] Snow Mountain\nPlease input a number: ")
	
	while map_selection not in ['1', '2', '3']:
		map_selection = input("Please select a map:\n\t[1] Forest\n\t[2] Cave\n\t[3] Snow Mountain\nPlease input a number: ")
		
	texture_path = os.getcwd() + '/../data/textures/'
	map_path = ''

	if map_selection == '1':
		map_path = os.getcwd() + '/../src/scenes/levels/forest_level.hpp'

	if map_selection == '2':
		map_path = os.getcwd() + '/../src/scenes/levels/cave_level.hpp'

	if map_selection == '3':
		map_path = os.getcwd() + '/../src/scenes/levels/snow_mountain_level.hpp'

	tile_map = get_tile_map(map_path)
	texture_map = get_texture_map(map_path, texture_path)
	texture_map['0'] = os.getcwd() + '/blank.png'
	texture_map['G'] = os.getcwd() + '/G.png'
	texture_map['P'] = os.getcwd() + '/P.png'

	working_img_v = None
	for y in range(0, len(tile_map)):
		working_img_h = None

		for x in range(0, len(tile_map[0])):
			if not working_img_h:
				working_img_h = Image.open(texture_map[tile_map[y][x]])
			else:
				new_img = Image.open(texture_map[tile_map[y][x]])
				new_img = new_img.resize([64,64], Image.ANTIALIAS)
				
				draw = ImageDraw.Draw(new_img)
				msg = str(x) + ',' + str(y)
				w, h = draw.textsize(msg)
				draw.text(((64-w)/2,(64-h)/2), msg, fill="red")
							
				working_img_h = get_concat_h(working_img_h, new_img)
		
		if not working_img_v:
			working_img_v = working_img_h
		else:
			working_img_v = get_concat_v(working_img_v, working_img_h)
	
	name = 'forest_map.png' if map_selection == '1' else 'cave_map.png' if map_selection == '2' else 'snow_mountain.png'
	working_img_v.save(name)
	working_img_v.show()
			
			

def get_tile_map(map_path):
	f = open(map_path, "r")
	hpp = f.read()
	start_index = hpp.index('const MapVector m_tile_vec')
	chunk = get_chunk(hpp[start_index:]).replace('\n', '').replace(' ', '').replace('\t', '')
	chunk_parts = chunk.split('}')

	tile_map = []
	i = 0
	for chunk_part in chunk_parts:
		if len(chunk_part) > 1:
			chunk_part = chunk_part.strip().replace(' ', '').replace('{', '').replace('}', '')
			tiles = chunk_part.split(',')
			tiles = list(filter(None, tiles))
			tile_map.append(tiles)
			
	return tile_map
	
	

def get_texture_map(map_path, texture_path):
	f = open(map_path, "r")
	hpp = f.read()
	start_index = hpp.index('const TexturePathMapping m_texture_map')
	chunk = get_chunk(hpp[start_index:]).replace('\n', '').replace(' ', '').replace('\t', '')
	chunk_parts = chunk.split('}')
	chunk_parts = list(filter(None, chunk_parts))
	texture_map = {}
	
	for chunk_part in chunk_parts:
		chunk_part = chunk_part[1:].replace('{', '')
		key_value = chunk_part.split(',')
		key_value[1] = key_value[1][key_value[1].index('(') + 2: key_value[1].index(')') - 1]
		texture_map[key_value[0]] = texture_path + key_value[1]
	
	return texture_map
		
	
	
def get_chunk(hpp):
	open_brackets = 1
	close_brackets = 0
	end_index = -1
	
	hpp = hpp[hpp.index('{'):]
	i = 1

	while open_brackets != close_brackets:
		if hpp[i] == '{':
			open_brackets +=1
		elif hpp[i] == '}':
			close_brackets += 1
		i += 1
		
	return hpp[:i]


def get_concat_h(im1, im2):
	dst = Image.new('RGB', (im1.width + im2.width, im1.height))
	dst.paste(im1, (0, 0))
	dst.paste(im2, (im1.width, 0))
	return dst

def get_concat_v(im1, im2):
	dst = Image.new('RGB', (im1.width, im1.height + im2.height))
	dst.paste(im1, (0, 0))
	dst.paste(im2, (0, im1.height))
	return dst	


if __name__ == '__main__':
	main()