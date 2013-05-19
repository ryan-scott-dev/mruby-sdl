MRuby::Gem::Specification.new('mruby-sdl') do |spec|
  spec.license = 'MIT'
  spec.authors = 'Ryan Scott'
  spec.version = '0.1.0'

  spec.linker.libraries << %w(SDL)

  if ENV['OS'] == 'Windows_NT'
    spec.linker.libraries << %w(SDLmain)
  end

  spec.requirements << "SDL >= 1.2.15"
end
