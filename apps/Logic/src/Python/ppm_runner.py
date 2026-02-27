import sys
import pygame

def start_screen(filename):
    """
    Returns the pygame reference of the screen to use with screen.blit.
    """
    with open(filename, "rt") as f:
        # Skip the first line (P3)
        f.readline()
        f.readline()

        # Read the dimensions
        width, height = map(int, ''.join(f.readline().split('\x00'))[:-1].split(' '))

        pygame.init()
        screen = pygame.display.set_mode((width, height))
        pygame.display.set_caption("PPM Image Viewer")

    return screen, width, height

def read_ppm(surface, file, width, height):
    
    # Skip the header lines
    file.readline()  
    file.readline()  
    file.readline()  
    file.readline()
    file.readline()
    file.readline()

    y = 0
    x = 0

    for line in file:
        if line.split('\x00')[1] != '\n':  # Ignore empty lines
            if y == height : continue

            # Parse RGB values
            r, g, b = map(int, ''.join(line.split('\x00'))[:-1].split(' '))
            #print(r, g, b)
            color = pygame.Color(r, g, b)
            surface.set_at((x, y), color)

            # Move to the next pixel
            x += 1
            if x >= width:
                x = 0
                y += 1

    file.close()


def decode(filename):
    file = open(filename, 'rt')
    screen, width, height = start_screen(filename)

    surface = pygame.Surface((width, height))

    # read and display the ppm image
    read_ppm(surface, file, width, height)

    # Blit the final surface and display it
    screen.blit(surface, (0, 0))
    pygame.display.flip()

    # Run the display loop
    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT or pygame.key.get_pressed()[pygame.K_ESCAPE]:
                running = False
            if event.type == pygame.key.get_pressed()[pygame.K_SPACE]:
                print("re calculating")
                read_ppm(surface, file, width, height)
                screen.blit(surface, (0,0))
                pygame.display.flip()

    pygame.quit()

if len(sys.argv) != 2:
    print("Usage: python ppm_runner.py <ppm_filename>")
    sys.exit(1)

filename = sys.argv[1]
decode(filename)
