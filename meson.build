project('Solis', 'cpp')
libsdl = dependency('SDL2')
libsdl_image = dependency('SDL2_image')
libgl = dependency('GL')
libglew = dependency('GLEW')

incdir = include_directories('./src')

source = [
    'src/Main.cc',
    'src/Image.cc',
    'src/Window.cc',
    'src/Module.cc',
    'src/Game/LevelGenerator.cc',
    'src/Game/Shooter.cc',
    'src/Input/Input.cc',
    'src/Input/InputEvent.cc',
    'src/Render/VAOManager.cc',
    'src/Render/VertexData.cc',
    'src/Render/VertexBuffer.cc',
    'src/Render/IndexBuffer.cc',
    'src/Render/Program.cc',
    'src/Render/Texture.cc',
    'src/Render/Renderer.cc'
]
executable('demo', source, include_directories : incdir, dependencies : [libgl, libsdl, libglew, libsdl_image])