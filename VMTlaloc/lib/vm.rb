require 'string'

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
      @global_memory[address.to_i] = value.to_s.rchomp if type == "string"
      @global_memory[address.to_i] = value.rchomp if type == "boolean"
      i += 1
    end

    @quadruples = file_lines.drop_while { |l| l != "$\n" }
    
  end
  
  def launch!
    i = 0
    while @quadruples[i] != nil and @quadruples[i] != "$$"
      operator, first_oper, second_oper, result = @quadruples[i].chomp("\n").split("\t")
      # Seccion para verificar si llega una variable como pointer (-000)
      if first_oper.to_i < 0
        first_oper = @global_memory[first_oper.to_i.abs]
      end
      if second_oper.to_i < 0
        second_oper = @global_memory[second_oper.to_i.abs]
      end
      if result.to_i < 0
        result = @global_memory[result.to_i.abs]
      end
      case operator.to_i
        when 213 # print()
          print @global_memory[first_oper.to_i] if second_oper.to_i == 0
          print @global_memory[second_oper.to_i + @global_memory[first_oper.to_i].to_i] if second_oper.to_i != 0
        when 228 # printline()
          puts @global_memory[first_oper.to_i] if second_oper.to_i == 0
          puts @global_memory[second_oper.to_i + @global_memory[first_oper.to_i].to_i] if second_oper.to_i != 0
        when 215 # readint()
          @global_memory[first_oper.to_i] = gets.to_i
        when 216 # readline()
          @global_memory[first_oper.to_i] = gets.to_s
        when 224 # return
          puts "return"
        when 197 # and
          if @global_memory[first_oper.to_i] == true and @global_memory[second_oper.to_i] == true
            @global_memory[result.to_i] = true 
          else
            @global_memory[result.to_i] = false
          end
        when 198 # or
          if @global_memory[first_oper.to_i] == true or @global_memory[second_oper.to_i] == true
            @global_memory[result.to_i] = true 
          else
            @global_memory[result.to_i] = false
          end
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
        when 205 # gotoF  gotoF de los estatutos if, while y for
          i = result.to_i - 1 if @global_memory[first_oper.to_i] == false or @global_memory[first_oper.to_i] == "false"      
        when 206 # goto de if/while. Se va hasta el final del if cuando es true. Se va al inicio del while.
          i = result.to_i - 1
        when 208 # gotoFor
          i = result.to_i - 1
        when 666 # step
          @global_memory[result.to_i] = @global_memory[first_oper.to_i] + @global_memory[second_oper.to_i]
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
            @global_memory[result.to_i] = @global_memory[first_oper.to_i].to_s + 
                                          @global_memory[second_oper.to_i].to_s
          else
            @global_memory[result.to_i] = @global_memory[first_oper.to_i] + @global_memory[second_oper.to_i]                    
          end
        when 45 # -
          @global_memory[result.to_i] = @global_memory[first_oper.to_i] - @global_memory[second_oper.to_i]
        when 42 # * - Diferente para la funcion de matrices
          if second_oper.to_i >= 5000            
            @global_memory[result.to_i] = @global_memory[first_oper.to_i] * @global_memory[second_oper.to_i]
          else
            @global_memory[result.to_i] = @global_memory[first_oper.to_i] * second_oper.to_i
          end 
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
        when 100 # VERifica para arrs
          if !(second_oper.to_i..result.to_i).cover?(@global_memory[first_oper.to_i])
            puts "Index out of bounds!"
            exit
          end
        when 501 # asignacion de arrs mediante variables por referencia *gm[result] = gm[first + gm[second]]
            #@global_memory[first_oper.to_i + @global_memory[second_oper.to_i]] = @global_memory[result.to_i]
            @global_memory[result.to_i] = first_oper.to_i + @global_memory[second_oper.to_i]
            #@global_memory[result.to_i] = @global_memory[first_oper.to_i + @global_memory[second_oper.to_i]] # 25010 + 6 = 25016
        end
    i += 1
    end
  end
  
end
