import { useRef, useEffect, useState } from "react";

type Props = {
  speed: number;
  acceleration: number;
  setScores: React.Dispatch<
    React.SetStateAction<{
      left: number;
      right: number;
    }>
  >;
  background: string;
};

const CANVAS_WIDTH = 1000;
const CANVAS_HEIGHT = 700;

export function Game({ speed, acceleration, setScores, background }: Props) {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const [leftPaddleY, setLeftPaddleY] = useState(100);
  const [rightPaddleY, setRightPaddleY] = useState(100);
  const [ball, setBall] = useState({
    x: CANVAS_WIDTH / 2,
    y: CANVAS_HEIGHT / 2,
    dx: 2,
    dy: 2,
  });

  const paddleWidth = 10;
  const paddleHeight = 100;
  const ballRadius = 5;
  const paddleSpeed = 10 * (speed / 5 + 1);

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
    if (e.key === "w" || e.key === "W")
      setLeftPaddleY((prev) => Math.max(prev - paddleSpeed, 0));
    if (e.key === "s" || e.key === "S")
      setLeftPaddleY((prev) =>
        Math.min(prev + paddleSpeed, CANVAS_HEIGHT - paddleHeight)
      );
    if (e.key === "ArrowUp")
      setRightPaddleY((prev) => Math.max(prev - paddleSpeed, 0));
    if (e.key === "ArrowDown")
      setRightPaddleY((prev) =>
        Math.min(prev + paddleSpeed, CANVAS_HEIGHT - paddleHeight)
      );
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
        dx = -dx;

        dx = Math.sign(dx) * Math.min(Math.abs(dx) + acceleration / 10, 10);
        dy = Math.sign(dy) * Math.min(Math.abs(dy) + acceleration / 10, 10);
      }

      // Ball reset on left or right edge
      // if (x - ballRadius < 0 || x + ballRadius > CANVAS_WIDTH) {
      //   x = CANVAS_WIDTH / 2;
      //   y = CANVAS_HEIGHT / 2;
      //   dx = 2;
      //   dy = 2;
      // }

      if (x - ballRadius < 0) {
        setScores((prev) => ({ ...prev, right: prev.right + 1 }));
        x = CANVAS_WIDTH / 2;
        y = CANVAS_HEIGHT / 2;
        dx = 2;
        dy = 2;
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

  useEffect(() => {
    const canvas = canvasRef.current;
    const ctx = canvas?.getContext("2d");

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
      }
    };

    const gameLoop = setInterval(() => {
      updateBall();
      draw();
    }, 1000 / 60); // 60 FPS

    window.addEventListener("keydown", keyDownHandler);

    return () => {
      clearInterval(gameLoop);
      window.removeEventListener("keydown", keyDownHandler);
    };
  }, [leftPaddleY, rightPaddleY, ball]);

  return (
    <div>
      <canvas
        ref={canvasRef}
        width={CANVAS_WIDTH}
        height={CANVAS_HEIGHT}
        style={{ border: "1px solid #000" }}
      />
      <pre>
        <code>
          {JSON.stringify({
            dx: ball.dx,
          })}
        </code>
      </pre>
    </div>
  );
}
