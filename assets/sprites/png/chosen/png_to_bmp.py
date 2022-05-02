from PIL import Image
import glob

images = glob.glob("*.png")
print(images)
for path in images:
    img = Image.open(path)
    r, g, b, a = img.split()
    img = Image.merge("RGB", (r, g, b))
    img = img.resize((32, 32), Image.Resampling.NEAREST)
    img.save(path.replace(".png", ".bmp"))