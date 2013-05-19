assert 'open window' do
  SDL.init
  window = SDL.set_video_mode(640, 480, 32, [:hw_surface, :double_buffer])

  SDL.quit

  !window.nil?
end