require 'Stack'

class Variables
  
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
  
   attr_reader :global_int
   attr_reader :global_decimal
   attr_reader :global_boolean
   attr_reader :global_string
   attr_reader :l_int
   attr_reader :l_float
   attr_reader :l_boolean
   attr_reader :l_string
   attr_reader :t_locales_int
   attr_reader :t_locales_decimal
   attr_reader :t_locales_boolean
   attr_reader :t_globales_int
   attr_reader :t_globales_decimal
   attr_reader :t_globales_boolean
   attr_reader :c_int
   attr_reader :c_decimal
   attr_reader :stack
   
   def initialize
     @global_int = {}
     @global_float = {}
     @global_boolean = {}
     @global_string = {}
     @l_int = {}
     @l_decimal = {}
     @l_boolean = {}
     @l_string = {}
     @t_locales_int = {}
     @t_locales_float = {}
     @t_locales_boolean = {}
     @t_globales_int = {}
     @t_globales_float = {}
     @t_globales_boolean = {}
     @constante_int = {}
     @constante_decimal = {}
     @stack = Stack.new
     @params = []
   end
   
    def create_variable(direccion, valor)
      direccion = direccion.to_i

      case direccion
        when GLOBAL_INT         then 
        when GLOBAL_STRING      then 
        when GLOBAL_BOOLEAN     then 
        when GLOBAL_DECIMAL     then 
        when LOCAL_INTEGERS     then 
        when LOCAL_STRINGS      then 
        when LOCAL_BOOLEANS     then 
        when LOCAL_DECIMALS     then 
        when T_INT              then 
        when T_STRING           then 
        when T_BOOLEAN          then 
        when T_DECIMALS         then 
        when C_INT              then 
        when C_STRING           then 
        when C_BOOLEAN          then 
        when C_DECIMAL          then 
      end
    end
    
    def get_variable(direccion)
            direccion = direccion.to_i

          case direccion
            when GLOBAL_INT         then @global_int[direccion]
            when GLOBAL_STRING      then @global_float[direccion]
            when GLOBAL_BOOLEAN     then @global_boolean[direccion]
            when GLOBAL_DECIMAL     then @global_string[direccion]
            when LOCAL_INTEGERS     then @l_int[direccion]
            when LOCAL_STRINGS      then @l_float[direccion]
            when LOCAL_BOOLEANS     then @l_boolean[direccion]
            when LOCAL_DECIMALS     then @l_string[direccion]
            when T_INT              then @t_globales_int[direccion]
            when T_STRING           then @t_globales_float[direccion]
            when T_BOOLEAN          then @t_globales_boolean[direccion]
            when T_DECIMALS         then @t_locales_int[direccion]
            when C_INT              then @t_locales_float[direccion]
            when C_STRING           then @t_locales_boolean[direccion]
            when C_BOOLEAN          then @constante_int[direccion]
            when C_DECIMAL          then @constante_decimal[direccion]
          end
    end
    
       def push_to_stack
         @stack.push(@l_int, @l_decimal, @l_boolean, @l_string,@t_locales_int, @t_locales_float, @t_locales_boolean)
         @l_int                = {}
         @l_decimal            = {}
         @l_boolean            = {}
         @l_string             = {}
         @t_locales_int        = {}
         @t_locales_decimal    = {}
         @t_locales_boolean    = {}
       end
       
      
        def pop_stack
          array_pop = @stack.pop
          @l_int                 = array_pop[0]
          @l_decimal             = array_pop[1]
          @l_boolean             = array_pop[2]
          @l_string              = array_pop[3]
          @tlocales_int          = array_pop[4]
          @tlocales_decimal      = array_pop[5]
          @tlocales_boolean      = array_pop[6]
          return array_pop[7].to_i
        end
        
        def push_persistance(persistance)
             @stack.push_persistance(persistance)
        end
  
end