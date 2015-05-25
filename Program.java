public class Program {
	public interface Visitor<T> {
		default void visit(Cons.Tuple<T> t) {}
		default void visit(Cons.Leaf<T> l) {}
	}

	public static <T> void preOrder(Cons<T> c, Visitor<T> v) {
		if (c.isTuple()) {
			Cons.Tuple<T> t = c.asTuple();
			v.visit(t);
			preOrder(t.left(), v);
			preOrder(t.right(), v);
		} else
			v.visit(c.asLeaf());
	}

	public static <T> Visitor<T> printVisitor()
		{ return new Visitor<T>()
			{ public void visit(Cons.Leaf<T> l) { System.out.println(l.value()); } }; }

	public static void main(String... args) {
		Cons<Integer> c = Cons.newTuple(Cons.newTuple(Cons.newLeaf(5),
                                                  Cons.newLeaf(4)),
                                    Cons.newTuple(Cons.newLeaf(3),
                                                  Cons.newLeaf(7)));
		preOrder(c, printVisitor());
	}
}
