I developed this project to gain a better understanding of the principles of object-oriented programming. Using C++, I implemented a shop that features three types of employees: a manager, who oversees the shop and helps maintain productivity; operators, who manage orders; and assistants, who support the operators.

Additionally, the shop offers three types of products in the rock category: t-shirts, discs, and vintage discs. To ensure the shop operates effectively, I implemented methods for managing employees and products, processing orders, and identifying the employees who processed the most orders. This includes determining the top three employees who managed the most expensive orders and the top three employees with the highest salaries. The shop can function only if it has at least one manager, three operators, and one assistant.

At any time, we can view details about the employees, such as their salary, name, date of hire, and type of employee. We can also access information about the products, including their name, quantity, price, type, and more. Furthermore, we can add or remove employees when hiring or firing, and similarly, we can add or delete products when receiving supplies or selling to customers. If an employee changes their name, we can update that information as well.

From a technical perspective, I used base classes: the base class Angajat, from which I derived the three types of employees—Manager, Operator, and Asistent—and the base class Produs, from which I derived the three types of products: ArticolVestimentar and Disc, with DiscVintage derived from Disc. In addition to these classes, I created the Magazin class to manage the shop, which includes methods for adding, deleting, and updating employees, verifying employee information, processing orders, finding top employees, and more.

Finally, to operate the shop, it retrieves information about employees, products, and orders from text files, as well as from keyboard input after the shop has been initialized using the data from the text files.
