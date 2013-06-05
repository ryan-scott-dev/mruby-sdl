assert 'open window' do
  SDL.init
  SDL.set_gl_version(3, 2)
  window = SDL::Window.create("Test Window", 0, 0, 640, 480, [:shown, :opengl])
  gl_context = window.create_gl_context

  GL.clear_color(0.3, 0.2, 0.5, 1)
  GL.clear [:color]
  window.swap_gl_window

  SDL.delay 1000

  gl_context.destroy
  window.destroy
  SDL.quit

  !window.nil?
end