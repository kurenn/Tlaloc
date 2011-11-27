require 'string'
require 'memory'

class VirtualMachine

  
  def initialize(input_file)
    file_lines = IO.readlines(input_file) # Convierte la lectura del archivo en lineas tipo string como arreglo
    @memory = Memory.new
    @quadruples = []
   
    i = 0   # Index de lineas leidas
    
    until file_lines[i] == "$$$\n"
      i += 1
    end
    
    i += 1
    until file_lines[i] == "$\n"
      value, type, address = file_lines[i].chomp("\n").split("\t")
      @memory.global_memory[address.to_i] = value.to_i if type == "integer"
      @memory.global_memory[address.to_i] = value.to_f if type == "decimal"
      @memory.global_memory[address.to_i] = value.to_s.rchomp if type == "string"
      @memory.global_memory[address.to_i] = value.rchomp if type == "boolean"
      #puts "#{@memory.global_memory[address.to_i]} : #{address.to_i}"
      i += 1
    end

    @quadruples = file_lines.drop_while { |l| l != "$\n" }
    
  end
  
  def launch!
    i = @quadruples[1].chomp("\n").split("\t")[3].to_i
    while @quadruples[i] != nil and @quadruples[i] != "$$"
      operator, first_oper, second_oper, result = @quadruples[i].chomp("\n").split("\t")
      
      # Seccion para verificar si llega una variable como pointer (-000)
      if first_oper.to_i < 0
        first_oper = @memory.global_memory[first_oper.to_i.abs]
      end
      if second_oper.to_i < 0
        second_oper = @memory.global_memory[second_oper.to_i.abs]
      end
      if result.to_i < 0
        result = @memory.global_memory[result.to_i.abs] 
      end
      
      case operator.to_i
        when 213 # print()
          print @memory.global_memory[first_oper.to_i] if second_oper.to_i == 0
          print @memory.global_memory[second_oper.to_i + @memory.global_memory[first_oper.to_i].to_i] if second_oper.to_i != 0
        when 228 # printline()
          puts @memory.global_memory[first_oper.to_i] if second_oper.to_i == 0
          puts @memory.global_memory[second_oper.to_i + @memory.global_memory[first_oper.to_i].to_i] if second_oper.to_i != 0
        when 215 # readint()
          @memory.global_memory[first_oper.to_i] = gets.to_i
        when 216 # readline()
          @memory.global_memory[first_oper.to_i] = gets.to_s
        when 224 # return
          @memory.global_memory[result.to_i] = @memory.global_memory[first_oper.to_i]
        when 197 # and
          if @memory.global_memory[first_oper.to_i] == true and @memory.global_memory[second_oper.to_i] == true
            @memory.global_memory[result.to_i] = true 
          else
            @memory.global_memory[result.to_i] = false
          end
        when 198 # or
          if @memory.global_memory[first_oper.to_i] == true or @memory.global_memory[second_oper.to_i] == true
            @memory.global_memory[result.to_i] = true 
          else
            @memory.global_memory[result.to_i] = false
          end
        when 212 # abs()
          @memory.global_memory[result.to_i] = @memory.global_memory[first_oper.to_i].abs
        when 214 # cos()
          @memory.global_memory[result.to_i] = Math.cos(@memory.global_memory[first_oper.to_i])
        when 225 # sin()
          @memory.global_memory[result.to_i] = Math.sin(@memory.global_memory[first_oper.to_i])
        when 211 # log
          @memory.global_memory[result.to_i] = Math.log10(@memory.global_memory[first_oper.to_i])
        when 226 # tan()
          @memory.global_memory[result.to_i] = Math.tan(@memory.global_memory[first_oper.to_i])
        when 231 # sqrt()
          @memory.global_memory[result.to_i] = Math.sqrt(@memory.global_memory[first_oper.to_i])
        when 166 # RET
          i = @memory.pop_stack
        when 205 # gotoF  gotoF de los estatutos if, while y for
          i = result.to_i - 1 if @memory.global_memory[first_oper.to_i] == false or @memory.global_memory[first_oper.to_i] == "false"      
        when 206 # goto de if/while. Se va hasta el final del if cuando es true. Se va al inicio del while.
          i = result.to_i - 1
        when 208 # gotoFor
          i = result.to_i - 1
        when 666 # step
          @memory.global_memory[result.to_i] = @memory.global_memory[first_oper.to_i] + @memory.global_memory[second_oper.to_i]
        when 61 # =
          @memory.global_memory[first_oper.to_i] = @memory.global_memory[result.to_i]
        when 122 # ==
          @memory.global_memory[result.to_i] = @memory.global_memory[first_oper.to_i] == @memory.global_memory[second_oper.to_i]
        when 60 # <
          @memory.global_memory[result.to_i] = @memory.global_memory[first_oper.to_i] < @memory.global_memory[second_oper.to_i]
        when 62 # >
          @memory.global_memory[result.to_i] = @memory.global_memory[first_oper.to_i] > @memory.global_memory[second_oper.to_i]
        when 123 # <>
          @memory.global_memory[result.to_i] = @memory.global_memory[first_oper.to_i] != @memory.global_memory[second_oper.to_i]
        when 43 # +
          if @memory.global_memory[first_oper.to_i].class == String or @memory.global_memory[second_oper.to_i].class == String
            @memory.global_memory[result.to_i] = @memory.global_memory[first_oper.to_i].to_s + 
                                          @memory.global_memory[second_oper.to_i].to_s
          else
            @memory.global_memory[result.to_i] = @memory.global_memory[first_oper.to_i] + @memory.global_memory[second_oper.to_i]
            #puts @memory.global_memory[result.to_i]                    
          end
        when 45 # -
          @memory.global_memory[result.to_i] = @memory.global_memory[first_oper.to_i] - @memory.global_memory[second_oper.to_i]
        when 42 # * - Diferente para la funcion de matrices
          if second_oper.to_i >= 5000       
            @memory.global_memory[result.to_i] = @memory.global_memory[first_oper.to_i] * @memory.global_memory[second_oper.to_i]
          else
            @memory.global_memory[result.to_i] = @memory.global_memory[first_oper.to_i] * second_oper.to_i
          end 
        when 47 # /
          @memory.global_memory[result.to_i] = @memory.global_memory[first_oper.to_i] / @memory.global_memory[second_oper.to_i]
        when 94 # ^
          @memory.global_memory[result.to_i] = @memory.global_memory[first_oper.to_i] ** @memory.global_memory[second_oper.to_i]
        when 107 # ->
          puts "->"
        when 33 # ! 
          puts "!"
        when 124 # >=
          @memory.global_memory[result.to_i] = @memory.global_memory[first_oper.to_i] >= @memory.global_memory[second_oper.to_i]
        when 125 # <=
          @memory.global_memory[result.to_i] = @memory.global_memory[first_oper.to_i] <= @memory.global_memory[second_oper.to_i]
        when 100 # VERifica para arrs
          if !(second_oper.to_i..result.to_i).cover?(@memory.global_memory[first_oper.to_i])
            puts "Index out of bounds!"
            exit
          end
        when 501 # asignacion de arrs mediante variables por referencia *gm[result] = gm[first + gm[second]]
          @memory.global_memory[result.to_i] = first_oper.to_i + @memory.global_memory[second_oper.to_i]
        when 209 #gosub - va a otra funcion como llamado
          @memory.push_to_stack(@memory.global_memory[25000..64999], i)
          @memory.init_params
          i = first_oper.to_i - 1
        when 900
          @memory.push_param(first_oper.to_i)
        end
    i += 1 #Incremento para recorrer todos los cuadruplos
    end
  end
  
end
