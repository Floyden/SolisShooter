project('Solis', 'cpp')
libsdl = dependency('SDL2')
libsdl_image = dependency('SDL2_image')
libgl = dependency('GL')
libglew = dependency('GLEW')

incdir = include_directories('./Source')

source = [
    'Source/Main.cc',
    'Source/Image.cc',
    'Source/Window.cc',
    'Source/Module.cc',
    'Source/Game/LevelGenerator.cc',
    'Source/Game/Shooter.cc',
    'Source/Input/Input.cc',
    'Source/Input/InputEvent.cc',
    'Source/Render/VAOManager.cc',
    'Source/Render/VertexData.cc',
    'Source/Render/VertexBuffer.cc',
    'Source/Render/IndexBuffer.cc',
    'Source/Render/Program.cc',
    'Source/Render/Texture.cc',
    'Source/Render/Renderer.cc'
]
executable('demo', source, include_directories : incdir, dependencies : [libgl, libsdl, libglew, libsdl_image])