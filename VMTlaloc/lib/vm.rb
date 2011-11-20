class VirtualMachine
  
  def initialize(input_file)
    file = File.new(input_file, "r")
    @procedures = []
    @quadruples = []
    @global_memory = [85000]  # Casillas asignadas para la memoria del programa
    
    while(line = file.gets || file.gets == "$")
      value, type, address = line.chomp.split(" ")
      @global_memory[address.to_i] = value.to_i if type == "integer"
      @global_memory[address.to_i] = value.to_f if type == "decimal"
      @global_memory[address.to_i] = value if type == "string"
    end
    file.close

    file = File.open(input_file)

    while(line = file.gets || file.gets == "$$")
      unless line == "$"      
        @quadruples << line.to_s
      end
    end
    
    file.close
    
  end
  
  def launch!
    @quadruples.each do |quadruple|
      operator, first_oper, second_oper, result = quadruple.chomp.split(" ")

      case operator.to_i
        when 213 # print()
          print @global_memory[first_oper.to_i]
        when 228 # printline()
          puts @global_memory[first_oper.to_i]
        when 215 # read()
          puts "read"
        when 224 # return
          puts "return"
        when 197 # and
          puts "and"
        when 198 # or
          puts "or"
        when 212 # abs()
          @global_memory[result.to_i] = @global_memory[first_oper.to_i].abs
        when 214 # cos()
          @global_memory[result.to_i] = Math.cos(@global_memory[first_oper.to_i])
        when 225 # sin()
          @global_memory[result.to_i] = Math.sin(@global_memory[first_oper.to_i])
        when 211 # log
          @global_memory[result.to_i] = Math.log10(@global_memory[first_oper.to_i])
        when 226 # tan()
          @global_memory[result.to_i] = Math.tan(@global_memory[first_oper.to_i])
        when 231 # sqrt()
          @global_memory[result.to_i] = Math.sqrt(@global_memory[first_oper.to_i])
        when 166 # RET
          puts "RET"
        when 217 # true
          puts "true"
        when 203 # false
          puts "false"
        when 205 # gotoF
          puts "gotoF"
        when 206 # goto
          puts "goto"
        when 207 # gotoV
          puts "gotoV"
        when 61 # =
          @global_memory[first_oper.to_i] = @global_memory[result.to_i]
        when 122 # ==
          puts "=="
        when 60 # <
          puts "<"
        when 62 # >
          puts ">"
        when 123 # <>
          puts "<>"
        when 43 # +
          @global_memory[result.to_i] = @global_memory[first_oper.to_i] + @global_memory[second_oper.to_i]
        when 45 # -
          @global_memory[result.to_i] = @global_memory[first_oper.to_i] - @global_memory[second_oper.to_i]
        when 42 # *
          @global_memory[result.to_i] = @global_memory[first_oper.to_i] * @global_memory[second_oper.to_i]
        when 47 # /
          @global_memory[result.to_i] = @global_memory[first_oper.to_i] / @global_memory[second_oper.to_i]
        when 94 # ^
          @global_memory[result.to_i] = @global_memory[first_oper.to_i] ** @global_memory[second_oper.to_i]
        when 107 # ->
          puts "->"
        when 33 # !
          puts "!"
        when 124 # >=
          puts ">="
        when 125 # <=
          puts "<="
      end
    end
  end
  
end
