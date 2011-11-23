class String
  
  def rchomp
    self.chomp("\"").reverse.chomp("\"").reverse
  end

  def to_boolean
      return self == "true"
  end
  
end
