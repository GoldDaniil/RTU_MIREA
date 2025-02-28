
from PIL import Image

def draw_black_background(width, height):
    img = Image.new('RGB', (width, height), (13, 13, 13))
    img.show()

draw_black_background(512, 512)

####---------------------------------------------------------------------------------------------------------------------

from PIL import Image, ImageDraw
import math

def draw_white_sphere(width, height):
    img = Image.new('RGB', (width, height), (13, 13, 13))
    draw = ImageDraw.Draw(img)

    cx, cy = width // 2, height // 2
    radius = int(0.4 * width)

    for y in range(height):
        for x in range(width):
            dx = x - cx
            dy = y - cy
            r = math.sqrt(dx * dx + dy * dy)
            if r < radius:
                draw.point((x, y), (255, 255, 255))

    img.show()


draw_white_sphere(512, 512)

####---------------------------------------------------------------------------------------------------------------------

from PIL import Image, ImageDraw
import math


def draw_sphere_with_gradient(width, height):
    img = Image.new('RGB', (width, height), (13, 13, 13))
    cx, cy = width // 2, height // 2
    radius = int(0.4 * width)

    for y in range(height):
        for x in range(width):
            dx = x - cx
            dy = y - cy
            r = math.sqrt(dx * dx + dy * dy)
            if r < radius:
                t = (y - (cy - radius)) / (2 * radius)#t для градиента по высоте
                r_col = 0.0
                g_col = int(t * 255)#0 - 255 зел канал
                b_col = int((1.0 - t) * 255)#255 - 0 син канал

                img.putpixel((x, y), (int(r_col), int(g_col), int(b_col)))#округляем значения к целым числам

    img.show()


draw_sphere_with_gradient(512, 512)

####---------------------------------------------------------------------------------------------------------------------

from PIL import Image, ImageDraw
import math


def draw_intermediate_gradient_sphere(width, height):
    img = Image.new('RGB', (width, height), (10, 10, 10))
    cx, cy = width // 2, height // 2
    radius = int(0.4 * width)

    for y in range(height):
        for x in range(width):
            dx = x - cx
            dy = y - cy
            r = math.sqrt(dx * dx + dy * dy)

            if r < radius:#check - until
                t = (y - (cy - radius)) / (2 * radius)#t для градиента по высоте

                shade = 1 - (r / radius) * 0.3#затемнение цвета для объемности

                r_col = 0
                g_col = int(t * 255 * shade)#0 - 255 зел канал + затем
                b_col = int((1.0 - t) * 255 * shade)#255 - 0 син канал + затем

                img.putpixel((x, y), (r_col, g_col, b_col))

    img.show()


draw_intermediate_gradient_sphere(512, 512)

####---------------------------------------------------------------------------------------------------------------------
from PIL import Image
import math


def draw_full_gradient_sphere(width, height):
    img = Image.new('RGB', (width, height), (13, 13, 13))
    cx, cy = width // 2, height // 2
    radius = int(0.4 * width)

    for y in range(height):
        for x in range(width):
            dx = x - cx
            dy = y - cy
            r = math.sqrt(dx * dx + dy * dy)
            mask = (1 - math.tanh((r - radius) * 20)) / 2

            # https://github.com/Harry24k/adversarial-attacks-pytorch/blob/master/torchattacks/attacks/cw.py

            if mask > 0.01:#только внутри сферы!!!
                t = (y - (cy - radius)) / (2 * radius)

                #градиент
                if t < 0.5:
                    f = t / 0.5
                    r_col = 0.5 + f * (1.0 - 0.5)
                    g_col = 1.0
                    b_col = 0.5 + f * (0.0 - 0.5)
                else:
                    f = (t - 0.5) / 0.5# от центра к низу
                    r_col = 1.0
                    g_col = 1.0 + f * (0.0 - 1.0)
                    b_col = 0.0

                bgBLACK = 0.05
                red = int((bgBLACK + mask * (r_col - bgBLACK)) * 255)
                green = int((bgBLACK + mask * (g_col - bgBLACK)) * 255)
                blue = int((bgBLACK + mask * (b_col - bgBLACK)) * 255)
                img.putpixel((x, y), (red, green, blue))

    img.show()


draw_full_gradient_sphere(512, 512)


