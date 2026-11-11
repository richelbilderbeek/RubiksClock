#!/usr/bin/env python3
"""Play the WebAssembly game on the 'Play' page of a built website.

Usage: test_play_page.py <URL of the play page>

The game must show the menu without a title bar,
clicking 'Start' must show the clock,
clicking a corner dial must turn it,
right-clicking or Shift-clicking it must turn it back,
'Flip' must show the back of the clock
and pressing Escape must go back to the menu.
"""
import io
import sys
import time

from PIL import Image, ImageChops, ImageStat
from playwright.sync_api import sync_playwright

START_TIMEOUT_SECS = 60
# The menu dialog has a gradient from #8080FF (top-left) to white,
# see qtrubiksclockmenudialog.ui
MENU_TOP_LEFT = (0x80, 0x80, 0xFF)
# The game has the same gradient, but where the menu shows its gradient
# the game shows the body of the clock
MENU_AT_BODY = (166, 166, 255)
# The body of the clock, left of the middle dial,
# see qtrubiksclockwidget.cpp
BODY = (40, 240)
FRONT_COLOR = (127, 127, 196)
BACK_COLOR = (96, 96, 196)
# Where the buttons are, see qtrubiksclockmenudialog.ui
# and qtrubiksclockmaindialog.ui
START_BUTTON = (200, 55)
FLIP_BUTTON = (100, 455)
# The center of the top-left dial, see qtrubiksclockwidget.cpp
TOP_LEFT_DIAL = (99, 137)
TOP_LEFT_DIAL_BOX = (59, 97, 139, 177)
MAX_COLOR_DIFF = 40  # Sum of the differences per color channel
MIN_TURN_DIFF = 0.5  # Average difference per color channel, from 0 to 255
MAX_SAME_DIFF = 0.1  # Average difference per color channel, from 0 to 255


def color_diff(color_a, color_b):
    """Sum of the differences per color channel."""
    return sum(abs(a - b) for a, b in zip(color_a, color_b))


def diff(image_a, image_b):
    """Average difference per color channel between two images."""
    stat = ImageStat.Stat(ImageChops.difference(image_a, image_b))
    return sum(stat.mean) / len(stat.mean)


def main():
    url = sys.argv[1]
    errors = []
    with sync_playwright() as playwright:
        browser = playwright.chromium.launch()
        page = browser.new_page(viewport={"width": 1280, "height": 1300})
        page.on("pageerror", lambda error: errors.append(str(error)))
        page.on("console", lambda m: print(f"console: {m.text}"))
        page.goto(url)
        frame = page.locator("iframe")

        def screenshot():
            data = frame.screenshot()
            return Image.open(io.BytesIO(data)).convert("RGB")

        def wait_for(position, color, what):
            deadline = time.time() + START_TIMEOUT_SECS
            pixel = screenshot().getpixel(position)
            while (time.time() < deadline
                   and color_diff(pixel, color) > MAX_COLOR_DIFF):
                print(f"Waiting for {what}, pixel at {position}: {pixel}")
                time.sleep(1)
                pixel = screenshot().getpixel(position)
            assert color_diff(pixel, color) <= MAX_COLOR_DIFF, \
                f"No {what} shown, pixel at {position} is {pixel}"

        def click(position, **kwargs):
            frame.click(position={"x": position[0], "y": position[1]},
                        **kwargs)
            time.sleep(0.5)

        def dial():
            return screenshot().crop(TOP_LEFT_DIAL_BOX)

        wait_for((5, 5), MENU_TOP_LEFT, "the menu")
        assert not errors, errors

        print("Clicking 'Start'")
        click(START_BUTTON)
        wait_for(BODY, FRONT_COLOR, "the front of the clock")

        before = dial()
        print("Clicking the top-left dial")
        click(TOP_LEFT_DIAL)
        turned = dial()
        turn_diff = diff(before, turned)
        print(f"Difference after turning: {turn_diff:.3f}")
        assert turn_diff > MIN_TURN_DIFF, "The dial did not turn"

        print("Right-clicking the top-left dial")
        click(TOP_LEFT_DIAL, button="right")
        back_diff = diff(before, dial())
        print(f"Difference after turning back: {back_diff:.3f}")
        assert back_diff < MAX_SAME_DIFF, \
            "Right-clicking did not turn the dial back"

        print("Clicking and then Shift-clicking the top-left dial")
        click(TOP_LEFT_DIAL)
        click(TOP_LEFT_DIAL, modifiers=["Shift"])
        back_diff = diff(before, dial())
        print(f"Difference after turning back: {back_diff:.3f}")
        assert back_diff < MAX_SAME_DIFF, \
            "Shift-clicking did not turn the dial back"

        print("Clicking 'Flip'")
        click(FLIP_BUTTON)
        wait_for(BODY, BACK_COLOR, "the back of the clock")

        print("Pressing Escape to go back to the menu")
        page.keyboard.press("Escape")
        wait_for(BODY, MENU_AT_BODY, "the menu")
        assert not errors, errors
        browser.close()
    print("OK: the game can be played")


if __name__ == "__main__":
    main()
