import time
import datetime

seconds = time.time()
formatted_seconds = f"{seconds:,.4f}"
scientific = f"{seconds:.2e}"

print(
    "Seconds since January 1, 1970: " +
    f"{formatted_seconds} or {scientific} in scientific notation"
)

now = datetime.datetime.now()
print(now.strftime("%b %d %Y"))
