assert 'open window' do
  SDL.init
  window = SDL::Window.create("Test Window", 0, 0, 640, 480, [:shown, :opengl])
  
  SDL.delay 1000

  window.destroy
  SDL.quit

  !window.nil?
end