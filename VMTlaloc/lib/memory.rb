#####
#    Compilador y Máquina Virtual para el lenguaje de programación Tláloc, como proyecto académico. 
#
#    Copyright (C) 2011 Eduardo López & Abraham Kuri
#
#    This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses/gpl.html.
#####

require 'stack'

class Memory
   
   GLOBAL_INT = 5000..9999
   GLOBAL_STRING = 10000..14999
   GLOBAL_BOOLEAN = 15000..19999
   GLOBAL_DECIMAL = 20000..24999
   LOCAL_INTEGERS = 25000..29999
   LOCAL_STRINGS = 30000..34999
   LOCAL_BOOLEANS = 35000..39999
   LOCAL_DECIMALS = 40000..44999
   T_INT = 45000..49999
   T_STRING = 50000..54999
   T_BOOLEAN = 55000..59999
   T_DECIMALS = 60000..64999
   C_INT = 65000..69999
   C_STRING = 70000..74999
   C_BOOLEAN = 75000..79999
   C_DECIMAL = 80000..84999
   
   attr_writer :global_memory
   attr_reader :global_memory
   
   def initialize
     @stack = Stack.new
     @params = Array.new
     @global_memory = [85000]  #Casillas asignadas para la memoria del programa
   end
   
   # Parametros que se mandan en el llamado
   def push_param(param)
    @params << [param, @global_memory[param]]
   end

   # Agrega variables locales y el index del cuadruplo donde se queda
   def push_to_stack(locals_and_temps, i)
     @stack.push(locals_and_temps, i)
     @global_memory[25000..64999].map{|gm| gm = nil}
   end
   
   # Resuelve parametros y arreglo auxiliar lo resetea para guardar valores para siguientes llamados
   def init_params
     int = LOCAL_INTEGERS.first
     string = LOCAL_STRINGS.first
     boolean = LOCAL_BOOLEANS.first
     decimal = LOCAL_DECIMALS.first
     
     integers_range = GLOBAL_INT.to_a + LOCAL_INTEGERS.to_a + T_INT.to_a + C_INT.to_a
     decimals_range = GLOBAL_DECIMAL.to_a + LOCAL_DECIMALS.to_a + T_DECIMALS.to_a + C_DECIMAL.to_a
     booleans_range = GLOBAL_BOOLEAN.to_a + LOCAL_BOOLEANS.to_a + T_BOOLEAN.to_a + C_BOOLEAN.to_a
     strings_range = GLOBAL_STRING.to_a + LOCAL_STRINGS.to_a + T_STRING.to_a + C_STRING.to_a

      @params.each do |param|
        case
        when integers_range.include?(param.first)
          @global_memory[int] = param.last
          int += 1
        when decimals_range.include?(param.first)
          @global_memory[decimal] = param.last
          decimal += 1
        when booleans_range.include?(param.first)
          @global_memory[boolean] = param.last
          boolean += 1
        when strings_range.include?(param.first) 
          @global_memory[string] = param.last
          string += 1
        end
      end
      @params = []
   end  
      
  def pop_stack
    variables_last_function = @stack.pop
    variables_last_function.first.each_with_index do |value, index|
      @global_memory[index + 25000] = value
    end
    return variables_last_function.last
  end
  
end
