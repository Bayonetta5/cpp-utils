0.1.4
=====

Maths
----

Add power<N>::of(number) that compute the power at compile time
add ker namespace

* Add kernel functions for learning machin in utils::ker namespace
* add template<typename T> T discretize(const T& tab,std::function<double(double)> f);
* add template<typename T,typename Iterator> T discretize(Iterator first,Iterator last,std::function<double(double)> f);

Log
---

add log::ok(args...) that print log in green

