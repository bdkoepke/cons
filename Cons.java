public interface Cons<T> {
	public static class Tuple<T> implements Cons<T> {
		private final Cons<T> left;
		private final Cons<T> right;
		public Cons<T> left() { return left; }
		public Cons<T> right() { return right; }
		private Tuple(Cons<T> left, Cons<T> right) { this.left = left; this.right = right; }
	}
	public static class Leaf<T> implements Cons<T> {
		private final T value;
		private Leaf(T value) { this.value = value; }
		public T value() { return this.value; }
	}

	public static <T> Tuple<T> newTuple(Cons<T> left, Cons<T> right) { return new Tuple<>(left, right); }
	public static <T> Leaf<T> newLeaf(T value) { return new Leaf<>(value); }

	default boolean isLeaf() { return this instanceof Leaf; }
	default boolean isTuple() { return ! isLeaf(); }
	default Tuple<T> asTuple() { assert isTuple(); return (Tuple<T>)this; }
	default Leaf<T> asLeaf() { assert isLeaf(); return (Leaf<T>)this; }
}
