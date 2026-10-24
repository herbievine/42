def NULL_not_found(object: any) -> int:

    obj_type = type(object)
    output = str()

    try:
        match object:
            case str() if not object:
                output = "Empty: "
            case float() if object != object:
                output = "Cheese: "
            case bool() if object is False:
                output = "Fake: "
            case int() if object == 0:
                output = "Zero: "
            case None:
                output = "Nothing: "
            case _:
                print("Type not found")
                return 1

        output += f"{object} {obj_type}"
        print(output)
        return 0

    except Exception as e:
        print(f"Error: {e}")
