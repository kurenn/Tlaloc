class VirtualMachine
  
  def initialize(input_file)
    file_lines = IO.readlines(input_file) # Convierte la lectura del archivo en lineas tipo string como arreglo
    @procedures = []
    @quadruples = []
    @global_memory = [85000]  # Casillas asignadas para la memoria del programa
    i = 0   # Index de lineas leidas
    
    until file_lines[i] == "$\n"
      value, type, address = file_lines[i].chomp("\n").split("\t")
      @global_memory[address.to_i] = value.to_i if type == "integer"
      @global_memory[address.to_i] = value.to_f if type == "decimal"
      @global_memory[address.to_i] = value.to_s if type == "string"
      i += 1
    end

    @quadruples = file_lines.drop_while { |l| l != "$\n" }
    
  end
  
  def launch!
    i = 0
    while @quadruples[i] != nil and @quadruples[i] != "$$"
      operator, first_oper, second_oper, result = @quadruples[i].chomp("\n").split("\t")
      case operator.to_i
        when 213 # print()
          print @global_memory[first_oper.to_i]
        when 228 # printline()
          puts @global_memory[first_oper.to_i]
        when 215 # readint()
          @global_memory[first_oper.to_i] = gets.to_i
        when 216 # readline()
          @global_memory[first_oper.to_i] = gets.to_s
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
        when 205 # gotoF  gotoF de los estatutos if, while y for
          i = result.to_i - 1 if @global_memory[first_oper.to_i] == false          
        when 206 # goto de if. Se va hasta el final del if cuando es true
          i = result.to_i - 1
        when 207 # gotoWhile
          puts "gotoW"
        when 208 # gotoFor
          puts "gotoW"
        when 61 # =
          @global_memory[first_oper.to_i] = @global_memory[result.to_i]
        when 122 # ==
          @global_memory[result.to_i] = @global_memory[first_oper.to_i] == @global_memory[second_oper.to_i]
        when 60 # <
          @global_memory[result.to_i] = @global_memory[first_oper.to_i] < @global_memory[second_oper.to_i]
        when 62 # >
          @global_memory[result.to_i] = @global_memory[first_oper.to_i] > @global_memory[second_oper.to_i]
        when 123 # <>
          @global_memory[result.to_i] = @global_memory[first_oper.to_i] != @global_memory[second_oper.to_i]
        when 43 # +
          if @global_memory[first_oper.to_i].class == String or @global_memory[second_oper.to_i].class == String
            @global_memory[result.to_i] = ("#{@global_memory[first_oper.to_i]}" + "#{@global_memory[second_oper.to_i]}").to_s  
          else
            @global_memory[result.to_i] = @global_memory[first_oper.to_i] + @global_memory[second_oper.to_i]                    
          end
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
          @global_memory[result.to_i] = @global_memory[first_oper.to_i] >= @global_memory[second_oper.to_i]
        when 125 # <=
          @global_memory[result.to_i] = @global_memory[first_oper.to_i] <= @global_memory[second_oper.to_i]
      end
    i += 1
    end
  end
  
end
