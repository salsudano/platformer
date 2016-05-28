def GetLinecountFromDir(dir)
	totalLines = 0
	Dir.glob("#{dir}/*").each { |file|
		next if file == "." || file == ".."
		if File.directory?(file)
			puts "File is dir! #{file}"
			totalLines += GetLinecountFromDir(file)
		else
			File.open(file, "r") { |file_contents|
				fileLines = 0
				file_contents.each_line { |line|
					fileLines += 1
				}
				puts "#{file}: #{fileLines}"
				totalLines += fileLines
			}
		end
	}
	puts "#{dir} total: #{totalLines}"
	return totalLines
end

GetLinecountFromDir(Dir.getwd())