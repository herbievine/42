import { useRef, useEffect, useState } from "react";
import { cn } from "../lib/cn";

// TODO: AI create more random movement
// TODO: the AIpaddle goes through the walls
// TODO: add keyboard control for the right paddle (real player)
// TODO: win on 10 points
// TODO: stop the AI when the game is paused

type Props = {
  speed: number;
  acceleration: number;
  background: string;
  aiSpeed: number;
  opponent: "ai" | "local";
  onWin: (data: {
    opponent: "ai" | "local";
    playerScore: number;
    opponentScore: number;
    playerExchanges: number;
    opponentExchanges: number;
  }) => void;
};

const CANVAS_WIDTH = 1000;
const CANVAS_HEIGHT = 700;

export function Game({
  speed,
  acceleration,
  background,
  aiSpeed,
  onWin,
  opponent,
}: Props) {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const [leftPaddleY, setLeftPaddleY] = useState(100);
  const [rightPaddleY, setRightPaddleY] = useState(100);
  const [pause, setPause] = useState(true);
  const [opponentExchanges, setOpponentExchanges] = useState(0);
  const [playerExchanges, setPlayerExchanges] = useState(0);
  const [ball, setBall] = useState({
    x: CANVAS_WIDTH / 2,
    y: CANVAS_HEIGHT / 2,
    dx: 2,
    dy: 2,
  });
  const [aiMoveUp, setAiMoveUp] = useState(true);
  const [aiBallY, setAiBallY] = useState(ball.y);
  const [ballReset, setBallReset] = useState(false);
  const [predictedY, setPredictedY] = useState(0);
  const ballRef = useRef(ball);
  const [keyPaddleLeftPressed, setKeyPaddleLeftPressed] = useState({
    up: false,
    down: false,
  });
  const [keyPaddleRightPressed, setKeyPaddleRightPressed] = useState({
    up: false,
    down: false,
  });

  const [scores, setScores] = useState({
    left: 0,
    right: 0,
  });

  const paddleWidth = 10;
  const paddleHeight = 100;
  const ballRadius = 5; //TODO: make it dynamic for vision friendly9
  const paddleSpeed = 4 * (speed / 5 + 1);
  const aiMaxSpeed = 4 * (aiSpeed / 5 + 1);

  const drawRect = (
    ctx: CanvasRenderingContext2D,
    x: number,
    y: number,
    width: number,
    height: number,
    color: string
  ) => {
    ctx.fillStyle = color;
    ctx.fillRect(x, y, width, height);
  };

  const drawBall = (
    ctx: CanvasRenderingContext2D,
    x: number,
    y: number,
    radius: number,
    color: string
  ) => {
    ctx.fillStyle = color;
    ctx.beginPath();
    ctx.arc(x, y, radius, 0, Math.PI * 2);
    ctx.fill();
  };

  const keyDownHandler = (e: KeyboardEvent) => {
    if (pause) {
      setKeyPaddleLeftPressed((prev) => ({ ...prev, up: false, down: false }));
      return;
    }
    if (e.key === "w" || e.key === "W")
      setKeyPaddleLeftPressed((prev) => ({ ...prev, up: true }));
    if (e.key === "s" || e.key === "S")
      setKeyPaddleLeftPressed((prev) => ({ ...prev, down: true }));
    if (opponent === "local") {
      if (e.key === "o" || e.key === "O")
        setKeyPaddleRightPressed((prev) => ({ ...prev, up: true }));
      if (e.key === "l" || e.key === "L")
        setKeyPaddleRightPressed((prev) => ({ ...prev, down: true }));
    } else if (opponent === "ai") {
      if (e.code === "F16")
        setKeyPaddleRightPressed((prev) => ({ ...prev, up: true }));
      if (e.code === "F17")
        setKeyPaddleRightPressed((prev) => ({ ...prev, down: true }));
    }
  };

  const keyUpHandler = (e: KeyboardEvent) => {
    if (pause) return;
    if (e.key === "w" || e.key === "W")
      setKeyPaddleLeftPressed((prev) => ({ ...prev, up: false }));
    if (e.key === "s" || e.key === "S")
      setKeyPaddleLeftPressed((prev) => ({ ...prev, down: false }));
    if (opponent === "local") {
      if (e.key === "o" || e.key === "O")
        setKeyPaddleRightPressed((prev) => ({ ...prev, up: false }));
      if (e.key === "l" || e.key === "L")
        setKeyPaddleRightPressed((prev) => ({ ...prev, down: false }));
    } else if (opponent === "ai") {
      if (e.code === "F16")
        setKeyPaddleRightPressed((prev) => ({ ...prev, up: false }));
      if (e.code === "F17")
        setKeyPaddleRightPressed((prev) => ({ ...prev, down: false }));
    }
  };

  // Function to trigger F16 key press programmatically
  const triggerF16KeyPress = () => {
    const event = new KeyboardEvent("keydown", {
      code: "F16",
      key: "F16",
      keyCode: 127,
      bubbles: true,
      cancelable: true,
    });
    window.dispatchEvent(event);

    // Release after timeToReachY
  };

  const triggerF16KeyRelease = () => {
    const event = new KeyboardEvent("keyup", {
      code: "F16",
      key: "F16",
      keyCode: 127,
      bubbles: true,
      cancelable: true,
    });
    window.dispatchEvent(event);
  };

  const triggerF17KeyPress = () => {
    const event = new KeyboardEvent("keydown", {
      code: "F17",
      key: "F17",
      keyCode: 128,
      bubbles: true,
      cancelable: true,
    });
    window.dispatchEvent(event);
  };

  const triggerF17KeyRelease = () => {
    const event = new KeyboardEvent("keyup", {
      code: "F17",
      key: "F17",
      keyCode: 128,
      bubbles: true,
      cancelable: true,
    });
    window.dispatchEvent(event);
  };

  const predictBallY = (
    ballX: number,
    ballY: number,
    ballDx: number,
    ballDy: number
  ) => {
    // predict y position of the ball when it reaches the right wall
    let predictedY = ballY + (ballDy * (CANVAS_WIDTH - ballX)) / ballDx;

    // simulate ball bouncing on top and bottom walls
    while (predictedY < 0 || predictedY > CANVAS_HEIGHT) {
      if (predictedY < 0) predictedY = -predictedY;
      if (predictedY > CANVAS_HEIGHT)
        predictedY = 2 * CANVAS_HEIGHT - predictedY;
    }

    return predictedY;
  };

  const updateBall = () => {
    setBall((prev) => {
      let { x, y, dx, dy } = prev;

      // Ball movement (speed 1-5)
      x += dx * (speed / 5 + 1);
      y += dy * (speed / 5 + 1);

      // Ball collision with top and bottom walls
      if (y - ballRadius < 0 || y + ballRadius > CANVAS_HEIGHT) {
        dy = -dy;
      }

      // Ball collision with paddles
      if (
        (x - ballRadius < paddleWidth + 20 &&
          y > leftPaddleY &&
          y < leftPaddleY + paddleHeight) ||
        (x + ballRadius > CANVAS_WIDTH - paddleWidth - 20 &&
          y > rightPaddleY &&
          y < rightPaddleY + paddleHeight)
      ) {
        if (dx < 0) {
          setPlayerExchanges((prev) => prev + 1);
        } else {
          setOpponentExchanges((prev) => prev + 1);
        }

        dx = -dx;

        dx = Math.sign(dx) * Math.min(Math.abs(dx) + acceleration / 10, 10);
        dy = Math.sign(dy) * Math.min(Math.abs(dy) + acceleration / 10, 10);
      }

      // Ball reset on left or right edge

      if (x - ballRadius < 0) {
        setScores((prev) => ({ ...prev, right: prev.right + 1 }));
        x = CANVAS_WIDTH / 2;
        y = CANVAS_HEIGHT / 2;
        dx = -2;
        dy = -2;
      } else if (x + ballRadius > CANVAS_WIDTH) {
        setScores((prev) => ({ ...prev, left: prev.left + 1 }));
        x = CANVAS_WIDTH / 2;
        y = CANVAS_HEIGHT / 2;
        dx = 2;
        dy = 2;
      }

      return { x, y, dx, dy };
    });
  };

  // player paddle movement
  const updatePlayerPaddle = () => {
    if (keyPaddleLeftPressed.up)
      setLeftPaddleY((prev) => Math.max(prev - paddleSpeed, 0));
    if (keyPaddleLeftPressed.down)
      setLeftPaddleY((prev) =>
        Math.min(prev + paddleSpeed, CANVAS_HEIGHT - paddleHeight)
      );

    if (opponent === "local") {
      if (keyPaddleRightPressed.up)
        setRightPaddleY((prev) => Math.max(prev - paddleSpeed, 0));
      if (keyPaddleRightPressed.down)
        setRightPaddleY((prev) =>
          Math.min(prev + paddleSpeed, CANVAS_HEIGHT - paddleHeight)
        );
    } else if (opponent === "ai") {
      if (keyPaddleRightPressed.up)
        setRightPaddleY((prev) => Math.max(prev - paddleSpeed, 0));
      if (keyPaddleRightPressed.down)
        setRightPaddleY((prev) =>
          Math.min(prev + paddleSpeed, CANVAS_HEIGHT - paddleHeight)
        );
    }
  };

  // ballRef is used to store the ball state between updates
  // useEffect(() => {}, [ball]);

  useEffect(() => {
    if (scores.left >= 5 || scores.right >= 5) {
      onWin({
        opponent,
        playerScore: scores.left,
        opponentScore: scores.right,
        playerExchanges,
        opponentExchanges,
      });
      setPause(true);
      setScores({ left: 0, right: 0 });
    }
  }, [scores]);

  useEffect(() => {
    // Interval to update predicted ball position every 1000ms (once per second)
    const aiUpdateInterval = setInterval(() => {
      const { x, y, dx, dy } = ballRef.current;
      const predicted = predictBallY(x, y, dx, dy);
      setPredictedY(predicted); // Update predicted Y position
    }, 1000);

    // Function to handle paddle movement based on prediction
    const moveAiPaddle = requestAnimationFrame(() => {
      // const paddleOffset = paddleHeight / 2;
      let distance = predictedY - (rightPaddleY + paddleHeight / 2); // Calculate distance

      if (distance > 0 && rightPaddleY + 100 >= CANVAS_HEIGHT) {
        distance = 0;
      } else if (distance < 0 && rightPaddleY <= 0) {
        distance = 0;
      }

      const direction = distance > 0 ? "down" : "up"; // Determine direction
      const tolerance = 5;

      // If the paddle is above the predicted Y and should move down
      if (Math.abs(distance) > tolerance) {
        if (direction === "up" && !keyPaddleRightPressed.up) {
          triggerF16KeyPress();
        } else if (direction === "down" && !keyPaddleRightPressed.down) {
          triggerF17KeyPress();
        }
      }

      if (
        (Math.abs(distance) >= 0 && Math.abs(distance) <= tolerance) ||
        (Math.abs(distance) <= 0 && Math.abs(distance) >= tolerance)
      ) {
        if (keyPaddleRightPressed.up) {
          triggerF16KeyRelease();
        }
        if (keyPaddleRightPressed.down) {
          triggerF17KeyRelease();
        }
      }
    });

    // Continuous movement check based on current state

    return () => {
      clearInterval(aiUpdateInterval); // Clean up ball prediction interval
      cancelAnimationFrame(moveAiPaddle); // Clean up paddle movement interval
    };
  }, [rightPaddleY, predictedY, keyPaddleRightPressed]); // Update when paddle or predicted Y changes

  useEffect(() => {
    const canvas = canvasRef.current;
    const ctx = canvas?.getContext("2d");

    ballRef.current = ball;

    const draw = () => {
      if (ctx) {
        ctx.clearRect(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);

        // Draw middle line
        ctx.beginPath();
        ctx.moveTo(CANVAS_WIDTH / 2, 0);
        ctx.lineTo(CANVAS_WIDTH / 2, CANVAS_HEIGHT);
        ctx.stroke();

        // Draw background
        drawRect(ctx, 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, background);

        // Draw paddles
        drawRect(ctx, 20, leftPaddleY, paddleWidth, paddleHeight, "#00FF00");
        drawRect(
          ctx,
          CANVAS_WIDTH - paddleWidth - 20,
          rightPaddleY,
          paddleWidth,
          paddleHeight,
          "#FF0000"
        );

        // Draw ball
        drawBall(ctx, ball.x, ball.y, ballRadius, "#0000FF");

        // Draw scores
        ctx.font = "30px Arial";
        ctx.fillText(scores.left.toString(), CANVAS_WIDTH / 2 - 50, 50);
        ctx.fillText(scores.right.toString(), CANVAS_WIDTH / 2 + 25, 50);
      }
    };

    const gameLoop = requestAnimationFrame(() => {
      if (pause) return;
      updateBall();
      updatePlayerPaddle();
      draw();
    });

    window.addEventListener("keydown", keyDownHandler);
    window.addEventListener("keyup", keyUpHandler);

    return () => {
      cancelAnimationFrame(gameLoop);
      window.removeEventListener("keydown", keyDownHandler);
      window.removeEventListener("keyup", keyUpHandler);
    };
  }, [
    leftPaddleY,
    rightPaddleY,
    ball,
    keyPaddleLeftPressed,
    keyPaddleRightPressed,
    pause,
  ]);

  return (
    <div className="relative origin-top-left w-[1000px] h-[700px]">
      <button
        className={cn(
          "absolute w-[1000px] h-[700px] top-0 left-0 bg-black/50 text-white text-3xl",
          pause === false && "hidden -z-10"
        )}
        onClick={() => {
          setPause(false);
          setBall({
            x: CANVAS_WIDTH / 2,
            y: CANVAS_HEIGHT / 2,
            dx: 2,
            dy: -1.4,
          });
        }}
      >
        Start game
      </button>
      <canvas
        ref={canvasRef}
        width={CANVAS_WIDTH}
        height={CANVAS_HEIGHT}
        style={{ border: "1px solid #000" }}
      />
    </div>
  );
}
