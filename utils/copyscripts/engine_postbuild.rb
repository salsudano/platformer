require 'fileutils'

$bin_dir = "../../libraries/SFML_2point1/bin/"

def main(args)
	output_dir = args[0]
	if !File.directory?("#{$bin_dir}")
		puts "bin_dir \"#{$bin_dir}\" doesn't exist!"
	elsif !File.directory?("#{output_dir}")
		puts "output_dir \"#{output_dir}\" doesn't exist!"
	else
		puts "Copying: #{$bin_dir}*.dll to #{output_dir}"
		FileUtils.cp("#{$bin_dir}*.dll", "#{output_dir}")		
	end
end

main(ARGV)