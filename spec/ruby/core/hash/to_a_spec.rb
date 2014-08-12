require File.expand_path('../../../spec_helper', __FILE__)
require File.expand_path('../fixtures/classes', __FILE__)

describe "Hash#to_a" do
  it "returns a list of [key, value] pairs with same order as each()" do
    h = new_hash(:a => 1, 1 => :a, 3 => :b, :b => 5)
    pairs = []

    h.each_pair do |key, value|
      pairs << [key, value]
    end

    h.to_a.should be_kind_of(Array)
    h.to_a.should == pairs
  end

  it "is called for Enumerable#entries" do
    h = new_hash(:a => 1, 1 => :a, 3 => :b, :b => 5)
    pairs = []

    h.each_pair do |key, value|
      pairs << [key, value]
    end

    ent = h.entries
    ent.should be_kind_of(Array)
    ent.should == pairs
  end

  it "returns a tainted array if self is tainted" do
    new_hash.taint.to_a.tainted?.should be_true
  end
end
