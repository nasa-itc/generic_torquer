require 'cosmos'
require 'cosmos/script'
require 'mission_lib.rb'

class TORQUER_LPT < Cosmos::Test
  def setup
    
  end

  def test_lpt
    start("tests/generic_torquer_lpt_test.rb")
  end

  def teardown

  end
end

class TORQUER_CPT < Cosmos::Test
  def setup
      
  end

  def test_cpt
    start("tests/generic_torquer_cpt_test.rb")
  end

  def teardown

  end
end

class Generic_torquer_Test < Cosmos::TestSuite
  def initialize
      super()
      add_test('TORQUER_CPT')
      add_test('TORQUER_LPT')
  end

  def setup
  end
  
  def teardown
  end
end