# simpleDialogUsingForms
- This project is made to prompt the user to enter information about a specimen and then save the user inputs into a JSON file.
- The project leverages capabilities such as :
- - Zoom in, Zoom Out, Zoom To Fit, Zoom to Item, Delete Selection, Draw with Pin, Draw Rectangle, Draw Line, Rubberband Selection, Panning, Erasing, Copying, Undo, Redo.
- OOP principles are used to use existing Qt objects and extend them.
- Understanding of the Meta-Object system is used to handle events and send signals or design slots.
- The main layout of the application looks as follows:
![image](https://user-images.githubusercontent.com/72888089/155899522-48e8835f-c90e-4cb0-b339-653f30c70428.png)
- Upon the user selection of the layout field, parameter 1 and 2 text change:
![image](https://user-images.githubusercontent.com/72888089/155899542-99fc8718-db97-473e-90c9-2822602e3cfb.png)
- Then the picture is modeled by pressing the visualize button
- ![image](https://user-images.githubusercontent.com/72888089/155899568-accb9099-1553-4698-add1-6a8ea662f88a.png)
- If one or more of the fiels is empty, the user will get a warning about it upon pressing save:
![image](https://user-images.githubusercontent.com/72888089/155899577-5d81b9ea-1c49-4fae-a043-35678614e16f.png)
- If all the fields are full, then the input will be saved to a Json file in the same folder and the user will get a prompt indicating this.
- The prompt goes away after 4 seconds which allows for other entries.
![image](https://user-images.githubusercontent.com/72888089/155899591-ae419cdb-d204-431e-9ac1-e019b95a3321.png)
- The JSON file:
![image](https://user-images.githubusercontent.com/72888089/147417798-414b61ed-60d9-4ebd-b225-dc1ea202a6c9.png)
- I have used a css stylesheet to set styles to the widget as desired
- ![image](https://user-images.githubusercontent.com/72888089/155899610-8d773a7d-0e17-4214-9545-6b0dbb4376f6.png)

