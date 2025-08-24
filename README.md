## Requirements

Make 4.4.1
GCC 14.2
RAYLIB 5.5


This document outlines the coding style and conventions to be followed.

## 1. **File Structure**

- Header files should be wrapped with include guards to avoid multiple inclusions:

  ```c
  #ifndef PHYSICS_H
  #define PHYSICS_H
  ...
  #endif // PHYSICS_H
  ```

## 2. **Naming Conventions**

- **Functions:** Function names should use `CamelCase` starting with a upercase letter.

`UpdatePhysicsDirection`, `UpdatePhysicsVelocity`

- **Structs:** Struct names should use `CamelCase` starting with an uppercase letter.

`Physics`

- **Variables:** Use `CamelCase` starting with a lowerase letter for local and parameter variables.

`vector`, `newSpeed`

## 3. **Function Design**

- Functions should be named descriptively, indicating the purpose or action performed.

`UpdatePhysicsDirection`, `UpdatePhysicsVelocity`

- Functions should take pointers when modifying variables outside their scope.

`void UpdatePhysicsDirection(Vector2 *direction, Vector2 vector)`

- Ensure function parameters have clear names to indicate their role.

`UpdatePhysicsVelocity(Vector2 *velocity, Vector2 *direction, float *speed)`

- Functions should be concise and focused on a single task. Avoid functions with multiple responsibilities.

## 4. **Struct Design**

 - Prefer composition, where structs are composed of other structs or primitive data types. This allows for more flexible and modular designs.

   ```c
   typedef struct {
    Vector2 position;
    Vector2 direction;
    Vector2 velocity;
    float speed;
    } Physics;
   ``` 
   
   Here, instead of trying to create a hierarchy of structs, we compose a Physics struct with relevant fields like `position`, `direction`, and `velocity`.

## 5. **Indentation & Formatting**

- **Indentation:** Use 1 tab for indentation. Never use spaces.
  
- **Spacing:** Place a single space after keywords like `if`, `for`, and `while`, and around operators (`=`, `+`, `-`, etc.) for readability.
  - Example: `*velocity = Vector2Scale(*direction, *speed * GetFrameTime());`

- **Braces:** Use braces `{}` even for single-line blocks for consistency and future-proofing. 

  ```c
  if (condition) {
      do_something();
  }
  ```

## 6. **Pointer Usage**

- Use pointers when passing large structures or when modifying variables outside the scope of the function. 

`Vector2 *position`, `float *speed`

- Avoid unnecessary dereferencing and use `*` clearly to indicate pointer dereferencing.

`*position = Vector2Add(*position, *velocity);`

## 7. **Consistency in Function Calls**

- When calling functions, parameters should be passed clearly, and care should be taken to avoid modifying data unintentionally unless needed.

  ```c
  UpdatePhysicsDirection(&physics->direction, direction);
  UpdatePhysicsVelocity(&physics->velocity, &physics->direction, &physics->speed);
  UpdatePhysicsPosition(&physics->position, &physics->velocity);
  ```

## 8. **Comments and Documentation**

- Strive for clarity through descriptive naming and simple logic.
- Add comments to explain non-obvious logic, design decisions, or complex algorithms.
- Do not state the obvious; let the code speak for itself where possible.

## 9. **End of File**

- Always ensure that header files end with the appropriate closing include guard and a new line after the last line of code:

  ```c
  #endif // PHYSICS_H

  ```

## 10. **General Rules**

- **Modular Design**:  Break code into small, focused functions and modules with clear interfaces.
- **Refactoring**: Regularly refactor code to maintain simplicity and performance
- **Don't Repeat Yourself**: Reuse code by creating helper functions to avoid duplication
- **Avoid magic numbers:** Use constants or defines instead of hardcoded values.
- **Code readability:** Prioritize code readability and maintainability over shortness or cleverness.
