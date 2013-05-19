SDL.init
SDL.set_video_mode(640, 480, 32, [:hw_surface, :double_buffer])
running = true

while running

  while(event = SDL.poll_event)
    if(event.type == :quit)
        running = false
    end
  end
end

SDL.quit